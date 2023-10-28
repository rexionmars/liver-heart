extern crate opencv;
use opencv::prelude::*;
use opencv::videoio;
use opencv::imgproc;
use opencv::core;
use opencv::highgui;
use std::sync::{Arc, Mutex};
use std::collections::HashMap;

struct TextRecognition {
    reader: tesseract::TessBaseAPI,
    video_capture: videoio::VideoCapture,
    last_frame: Mat,
    rois: Vec<core::Rect>,
    current_roi: Option<core::Rect>,
    drawing: bool,
    deleted_rois: Vec<core::Rect>,
    running: bool,
    event_queue: Arc<Mutex<Vec<i32>>,
}

impl TextRecognition {
    fn new(video_source: &str, language: &str) -> Self {
        let mut reader = tesseract::TessBaseAPI::create().unwrap();
        reader.init(None, language).unwrap();
        reader.set_variable("tessedit_char_whitelist", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789").unwrap();

        let mut video_capture = videoio::VideoCapture::new(&video_source, videoio::CAP_FFMPEG).unwrap();
        let mut last_frame = Mat::default().unwrap();
        video_capture.read(&mut last_frame);

        TextRecognition {
            reader,
            video_capture,
            last_frame,
            rois: Vec::new(),
            current_roi: None,
            drawing: false,
            deleted_rois: Vec::new(),
            running: true,
            event_queue: Arc::new(Mutex::new(Vec::new())),
        }
    }

    fn start(&mut self) {
        let event_queue = self.event_queue.clone();

        let video_thread = std::thread::spawn(move || {
            let mut video_capture = videoio::VideoCapture::default().unwrap();
            video_capture.open("http://192.168.0.38:81/stream", videoio::CAP_FFMPEG).unwrap();

            while self.running {
                let mut frame = Mat::default().unwrap();
                video_capture.read(&mut frame);

                if frame.size().unwrap().width > 0 && frame.size().unwrap().height > 0 {
                    self.read_text(&mut frame);
                }
            }
        });

        let user_input_thread = std::thread::spawn(move || {
            loop {
                let key = highgui::wait_key(1).unwrap();
                if key == 27 || key == 113 {
                    break;
                } else if key == 100 {
                    self.remove_last_roi();
                } else if key == 117 {
                    self.undo_roi_deletion();
                }
                event_queue.lock().unwrap().push(key);
            }
        });

        self.display_window();
        video_thread.join().unwrap();
        user_input_thread.join().unwrap();
    }

    fn read_text(&mut self, frame: &mut Mat) {
        let mut roi_data = HashMap::new();

        for (i, roi) in self.rois.iter().enumerate() {
            let mut cropped_frame = Mat::default().unwrap();
            frame.roi_sub_mat(&mut cropped_frame, &*roi).unwrap();
            
            let mut results = tesseract::ResultIterator::new(&self.reader, &cropped_frame);
            results.begin();
            
            let mut roi_info = HashMap::new();
            let mut list_value = Vec::new();

            while results.is_valid() {
                let text = results.get_utf8_text(tesseract::RIL_TEXTLINE).unwrap_or("").to_string();
                let (label, value) = self.extract_label_and_value(&text);
                list_value.push(value);

                if !label.is_empty() {
                    roi_info.entry(label).or_insert(Vec::new()).push(value);
                }

                let mut bounding_box = core::Rect::default().unwrap();
                results.get_bounding_box(tesseract::RIL_TEXTLINE, 0, 0, &mut bounding_box);

                let text_x = roi.x + bounding_box.x;
                let text_y = roi.y + bounding_box.y;
                let point1 = core::Point { x: text_x, y: text_y };
                let point2 = core::Point { x: roi.x + bounding_box.width, y: roi.y + bounding_box.height };
                imgproc::rectangle(frame, point1, point2, core::Scalar::new(0.0, 255.0, 0.0, 0.0), 1, 8, 0).unwrap();
                imgproc::put_text(frame, &text, core::Point { x: text_x, y: text_y - 10 }, core::FONT_HERSHEY_SIMPLEX, 0.5, core::Scalar::new(0.0, 255.0, 0.0, 0.0), 1, 8, false).unwrap();
                
                results.next(tesseract::RIL_TEXTLINE);
            }

            let filtered_values: Vec<_> = list_value.iter().filter_map(|&x| x).collect();
            let filtered_values: Vec<f32> = filtered_values.iter().map(|&x| x).collect();
            for (label, values) in roi_info.iter_mut() {
                values.extend(&filtered_values);
            }

            roi_data.insert(format!("ROI_ID {}", i), roi_info);
        }

        println!("{:#?}", roi_data);
        self.print_roi_data(&roi_data);

        for roi in &self.rois {
            imgproc::rectangle(frame, roi.tl(), roi.br(), core::Scalar::new(214.0, 102.0, 3.0, 0.0), 1, 8, 0).unwrap();
        }

        if let Some(current_roi) = &self.current_roi {
            imgproc::rectangle(frame, current_roi.tl(), current_roi.br(), core::Scalar::new(129.0, 23.0, 255.0, 0.0), 1, 8, 0).unwrap();
        }

        self.last_frame = frame.clone();
    }

    fn print_roi_data(&self, roi_data: &HashMap<String, HashMap<String, Vec<f32>>) {
        // Your code to print ROI data goes here
    }

    fn extract_label_and_value(&self, text: &str) -> (String, Option<f32>) {
        let parts: Vec<&str> = text.splitn(2, char::is_numeric).collect();
        let label = parts[0].trim().to_string();
        let value = if parts.len() > 1 {
            parts[1].trim().parse::<f32>().ok()
        } else {
            None
        };
        (label, value)
    }

    fn display_window(&self) {
        highgui::named_window("Text Recognition", 1).unwrap();
        highgui::set_mouse_callback("Text Recognition", &Self::on_mouse_events, &self);

        while self.running {
            if let Some(ref last_frame) = self.last_frame {
                highgui::imshow("Text Recognition", last_frame).unwrap();
            }

            let key = highgui::wait_key(1).unwrap();
            self.event_queue.lock().unwrap().push(key);
        }
    }

    fn on_mouse_events(event: i32, x: i32
