#include <opencv2/opencv.hpp>
#include <easyocr.h>
#include <json/json.h>
#include <regex>
#include <thread>
#include <queue>
#include <iostream>

class TextRecognition {
public:
    TextRecognition(const std::string& videoSource, const std::string& language = "en") :
        reader({language}),
        video_capture(videoSource),
        last_frame(nullptr),
        current_roi(nullptr),
        drawing(false),
        running(true) {
    }

    void start() {
        std::thread video_thread(&TextRecognition::videoProcessingThread, this);
        std::thread user_input_thread(&TextRecognition::handleUserInput, this);
        displayWindow();
        video_thread.join();
        user_input_thread.join();
    }

    void readText(cv::Mat frame) {
        if (frame.empty()) {
            return;
        }

        std::map<std::string, std::map<std::string, std::vector<float>>> roi_data;

        for (size_t i = 0; i < rois.size(); ++i) {
            cv::Rect roi = rois[i];
            cv::Mat cropped_frame = frame(roi);
            std::vector<easyocr::Result> results = reader.readtext(cropped_frame);

            std::map<std::string, std::vector<float>> roi_info;
            std::vector<float> list_value;

            for (const easyocr::Result& result : results) {
                std::string text = result.text;
                std::string label, value;
                std::tie(label, value) = extractLabelAndValue(text);

                list_value.push_back(std::stof(value));

                if (!label.empty()) {
                    roi_info[label].push_back(std::stof(value));
                }

                cv::Rect bbox = result.bbox;
                int text_x = roi.x + bbox.x;
                int text_y = roi.y + bbox.y;
                cv::rectangle(frame, cv::Point(text_x, text_y), cv::Point(roi.x + bbox.x + bbox.width, roi.y + bbox.y + bbox.height), cv::Scalar(0, 255, 0), 1);
                cv::putText(frame, text, cv::Point(text_x, text_y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);
            }

            roi_info["ROI_ID " + std::to_string(i)] = list_value;
            roi_data["ROI_ID " + std::to_string(i)] = roi_info;
        }

        std::cout << roi_data << std::endl;

        printRoiData(roi_data);

        for (const cv::Rect& roi : rois) {
            cv::rectangle(frame, roi, cv::Scalar(214, 102, 3), 1);
        }

        if (current_roi) {
            cv::rectangle(frame, *current_roi, cv::Scalar(129, 23, 255), 1);
        }

        last_frame = frame;
    }

    void printRoiData(const std::map<std::string, std::map<std::string, std::vector<float>>&> roi_data) {
        // Your code to print ROI data goes here
    }

    std::pair<std::string, std::string> extractLabelAndValue(const std::string& text) {
        static const std::regex pattern("([a-zA-Z]+)\\s*([0-9]+\\.?[0-9]*)");
        std::smatch match;
        if (std::regex_search(text, match, pattern)) {
            return {match[1].str(), match[2].str()};
        }
        return {"", ""};
    }

    void videoProcessingThread() {
        while (running) {
            cv::Mat frame;
            video_capture >> frame;
            readText(frame);
        }
    }

    void displayWindow() {
        cv::namedWindow("Text Recognition");
        cv::setMouseCallback("Text Recognition", &TextRecognition::onMouseEvents, this);

        while (running) {
            if (last_frame) {
                cv::imshow("Text Recognition", last_frame);
            }

            int key = cv::waitKey(1) & 0xFF;
            event_queue.push(key);
        }

        video_capture.release();
        cv::destroyAllWindows();
    }

    static void onMouseEvents(int event, int x, int y, int flags, void* userdata) {
        TextRecognition* instance = static_cast<TextRecognition*>(userdata);
        instance->onMouseEventsCallback(event, x, y, flags);
    }

    void onMouseEventsCallback(int event, int x, int y, int flags) {
        if (event == cv::EVENT_LBUTTONDOWN) {
            drawing = true;
            current_roi = std::make_unique<cv::Rect>(x, y, 0, 0);
        }
        else if (event == cv::EVENT_MOUSEMOVE && drawing) {
            current_roi->width = x - current_roi->x;
            current_roi->height = y - current_roi->y;
        }
        else if (event == cv::EVENT_LBUTTONUP) {
            drawing = false;
            rois.push_back(*current_roi);
            current_roi.reset();
        }
    }

    void removeLastRoi() {
        if (!rois.empty()) {
            deleted_rois.push_back(rois.back());
            rois.pop_back();
        }
    }

    void undoRoiDeletion() {
        if (!deleted_rois.empty()) {
            rois.push_back(deleted_rois.back());
            deleted_rois.pop_back();
        }
    }

    void handleUserInput() {
        while (running) {
            int key = event_queue.pop();
            if (key == 'q' || key == 27) {  // 'q' or ESC key
                running = false;
            }
            else if (key == 'd') {
                removeLastRoi();
            }
            else if (key == 'u') {
                undoRoiDeletion();
            }
        }
    }

private:
    easyocr::Reader reader;
    cv::VideoCapture video_capture;
    cv::Mat last_frame;
    std::vector<cv::Rect> rois;
    std::unique_ptr<cv::Rect> current_roi;
    bool drawing;
    bool running;
    std::queue<int> event_queue;
    std::vector<cv::Rect> deleted_rois;
};

int main() {
    TextRecognition text_recognition("http://192.168.0.38:81/stream"); // OV2640
    text_recognition.start();
    return 0;
}
