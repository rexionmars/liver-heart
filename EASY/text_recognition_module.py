import cv2
import easyocr

import sys
import os
import threading

class TextRecognition:
    def __init__(self, video_source, language='en'):
        self.reader = easyocr.Reader([language])
        self.video_capture = VideoCapture(video_source)
        self.last_frame = None
        self.x_position = 200
        self.y_position = 200
        self.crop_width = 200
        self.crop_height = 200

    def start(self):
        video_thread = threading.Thread(target=self.video_processing_thread)
        video_thread.start()
        self.display_window()

    def read_text(self, frame):
        if frame is None:
            return

        cropped_frame = frame[self.y_position:self.y_position + self.crop_height, self.x_position:self.x_position + self.crop_width]
        results = self.reader.readtext(cropped_frame)

        for (bbox, text, prob) in results:
            (top_left, top_right, bottom_right, bottom_left) = bbox
            top_left = tuple(map(int, top_left))
            bottom_right = tuple(map(int, bottom_right))

            top_left = (top_left[0] + self.x_position, top_left[1] + self.y_position)
            bottom_right = (bottom_right[0] + self.x_position, bottom_right[1] + self.y_position)

            cv2.rectangle(frame, top_left, bottom_right, (0, 255, 0), 1)
            cv2.putText(frame, text, (top_left[0], top_left[1] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 1)
            print(f"Text: {text} Prob: {prob:.2f}")

        cv2.rectangle(frame, (self.x_position, self.y_position), (self.x_position + self.crop_width, self.y_position + self.crop_height), (0, 0, 255), 1)
        self.last_frame = frame

    def video_processing_thread(self):
        while True:
            ret, frame = self.video_capture.read()
            self.read_text(frame)

    def display_window(self):
        cv2.namedWindow('Text Recognition')
        cv2.createTrackbar('X Position', 'Text Recognition', self.x_position, self.video_capture.width, self.on_x_position_change)
        cv2.createTrackbar('Y Position', 'Text Recognition', self.y_position, self.video_capture.height, self.on_y_position_change)
        cv2.createTrackbar('Crop Width', 'Text Recognition', self.crop_width, self.video_capture.width, self.on_crop_width_change)
        cv2.createTrackbar('Crop Height', 'Text Recognition', self.crop_height, self.video_capture.height, self.on_crop_height_change)

        while True:
            self.update_trackbar_values()
            if self.last_frame is not None:
                cv2.imshow('Text Recognition', self.last_frame)

            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

        self.video_capture.release()
        cv2.destroyAllWindows()

    def on_x_position_change(self, val):
        self.x_position = val

    def on_y_position_change(self, val):
        self.y_position = val

    def on_crop_width_change(self, val):
        self.crop_width = val

    def on_crop_height_change(self, val):
        self.crop_height = val

    def update_trackbar_values(self):
        self.x_position = cv2.getTrackbarPos('X Position', 'Text Recognition')
        self.y_position = cv2.getTrackbarPos('Y Position', 'Text Recognition')
        self.crop_width = cv2.getTrackbarPos('Crop Width', 'Text Recognition')
        self.crop_height = cv2.getTrackbarPos('Crop Height', 'Text Recognition')


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
    text_recognition = TextRecognition('http://192.168.0.51:81/stream')
    text_recognition.start()
