import cv2
import easyocr
import threading
import json
import re
import sys
from queue import Queue

class TextRecognition:
    def __init__(self, video_source, language="en"):
        self.reader = easyocr.Reader([language])
        self.video_capture = VideoCapture(video_source)
        self.last_frame = None
        self.rois = []  # List to store ROIs
        self.current_roi = None  # The currently being created ROI
        self.drawing = False  # Flag to indicate if we are drawing an ROI
        self.deleted_rois = []  # List to store deleted ROIs
        self.running = True  # Flag to indicate if the program is running

        # Create a queue to handle user events
        self.event_queue = Queue()

    def start(self):
        video_thread = threading.Thread(target=self.video_processing_thread)
        video_thread.start()
        user_input_thread = threading.Thread(target=self.handle_user_input)
        user_input_thread.start()
        self.display_window()

    def read_text(self, frame):
        if frame is None:
            return

        roi_data = {}  # Dictionary to store ROI data

        for i, roi in enumerate(self.rois):
            x, y, w, h = roi
            cropped_frame = frame[y:y + h, x:x + w]

            if cropped_frame is not None and not cropped_frame.size == 0:
                results = self.reader.readtext(cropped_frame)
            else:
                continue  # Skip processing if cropped_frame is empty

            roi_info = {}  # Dictionary to store current ROI information

            lista = []
            for bbox, text, prob in results:
                label, value = self.extract_label_and_value(text)

                lista.append(text)
                lista2 = []
                for i in lista:
                    lista2.append(i)

                if len(lista2) > 1:
                    outuput = {
                        f"{lista2[0]}": lista2[1]
                    }

                    print(json.dumps(outuput, indent=4))

                if label:
                    roi_info[label] = value

                # Render text detection on the frame within the ROI
                text_x = x + bbox[0][0]
                text_y = y + bbox[0][1]
                cv2.rectangle(frame, (text_x, text_y), (x + bbox[2][0], y + bbox[2][1]), (0, 255, 0), 1)
                cv2.putText(
                    frame,
                    text,
                    (text_x, text_y - 10),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.5,
                    (0, 255, 0),
                    1,
                )

            roi_data[f"ROI_ID {i}"] = roi_info

        # Print ROI data, including numeric values
        self.print_roi_data(roi_data)

        for roi in self.rois:
            x, y, w, h = roi
            cv2.rectangle(
                frame,
                (x, y),
                (x + w, y + h),
                (214, 102, 3),
                1,
            )

        if self.current_roi is not None:
            x, y, w, h = self.current_roi
            cv2.rectangle(
                frame,
                (x, y),
                (x + w, y + h),
                (129, 23, 255),
                1,
            )

        self.last_frame = frame

    def print_roi_data(self, roi_data):
        #for roi_id, data in roi_data.items:
            #print(f"ROI {roi_id}:")
            #for label, value in data.items:
                #print(f"{label}: {value}")
        ...

    def extract_label_and_value(self, text):
        parts = re.split(r'(\d+)', text)
        label = parts[0].strip()
        value = parts[1].strip() if len(parts) > 1 else None
        return label, value

    def video_processing_thread(self):
        while self.running:
            ret, frame = self.video_capture.read()
            self.read_text(frame)

    def display_window(self):
        cv2.namedWindow("Text Recognition")
        cv2.setMouseCallback("Text Recognition", self.on_mouse_events)

        while self.running:
            if self.last_frame is not None:
                cv2.imshow("Text Recognition", self.last_frame)

            key = cv2.waitKey(1) & 0xFF
            self.event_queue.put(key)

        self.video_capture.release()
        cv2.destroyAllWindows()

    def on_mouse_events(self, event, x, y, flags, param):
        if event == cv2.EVENT_LBUTTONDOWN:
            self.drawing = True
            self.current_roi = [x, y, 0, 0]

        elif event == cv2.EVENT_MOUSEMOVE and self.drawing:
            self.current_roi[2] = x - self.current_roi[0]
            self.current_roi[3] = y - self.current_roi[1]

        elif event == cv2.EVENT_LBUTTONUP:
            self.drawing = False
            self.rois.append(tuple(self.current_roi))
            self.current_roi = None

    def remove_last_roi(self):
        if self.rois:
            self.deleted_rois.append(self.rois.pop())

    def undo_roi_deletion(self):
        if self.deleted_rois:
            self.rois.append(self.deleted_rois.pop())

    def handle_user_input(self):
        while self.running:
            key = self.event_queue.get()
            if key == ord("q") or key == 27:  # 27 é o valor da tecla ESC
                self.running = False
            elif key == ord("d"):
                self.remove_last_roi()
            elif key == ord("u"):
                self.undo_roi_deletion()

class VideoCapture:
    def __init__(self, source):
        self.cap = cv2.VideoCapture(source)
        self.width = int(self.cap.get(cv2.CAP_PROP_FRAME_WIDTH))
        self.height = int(self.cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

    def read(self):
        return self.cap.read()

    def release(self):
        self.cap.release()

if __name__ == "__main__":
    text_recognition = TextRecognition("http://192.168.0.51:81/stream")
    text_recognition.start()
    while text_recognition.running:
        pass  # Aguarde até que a tecla "q" ou "ESC" seja pressionada
    sys.exit(0)  # Saia do programa adequadamente após a tecla "q" ou "ESC" ser pressionada
