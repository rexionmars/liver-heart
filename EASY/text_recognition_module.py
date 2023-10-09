
import cv2
import easyocr
import threading

class TextRecognition:
    def __init__(self, video_source, language="en"):
        self.reader = easyocr.Reader([language])
        self.video_capture = VideoCapture(video_source)
        self.last_frame = None
        self.rois = []  # Lista para armazenar as ROIs
        self.selected_roi = None
        self.dragging = False

    def start(self):
        video_thread = threading.Thread(target=self.video_processing_thread)
        video_thread.start()
        self.display_window()

    def read_text(self, frame):
        if frame is None:
            return

        for roi in self.rois:
            x, y, w, h = roi
            cropped_frame = frame[y:y+h, x:x+w]
            results = self.reader.readtext(cropped_frame)

            for bbox, text, prob in results:
                (top_left, top_right, bottom_right, bottom_left) = bbox
                top_left = tuple(map(int, top_left))
                bottom_right = tuple(map(int, bottom_right))

                top_left = (top_left[0] + x, top_left[1] + y)
                bottom_right = (bottom_right[0] + x, bottom_right[1] + y)

                cv2.rectangle(frame, top_left, bottom_right, (0, 255, 0), 1)
                cv2.putText(
                    frame,
                    text,
                    (top_left[0], top_left[1] - 10),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.5,
                    (0, 255, 0),
                    1,
                )
                print(f"Text: {text} Prob: {prob}")

            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 1)
        self.last_frame = frame

    def video_processing_thread(self):
        while True:
            ret, frame = self.video_capture.read()
            self.read_text(frame)

    def display_window(self):
        cv2.namedWindow("Text Recognition")
        cv2.setMouseCallback("Text Recognition", self.on_mouse_event)
        self.update_trackbar_values()

        while True:
            if self.last_frame is not None:
                cv2.imshow("Text Recognition", self.last_frame)

            if cv2.waitKey(1) & 0xFF == ord("q"):
                break

        self.video_capture.release()
        cv2.destroyAllWindows()

    def on_mouse_event(self, event, x, y, flags, param):
        if event == cv2.EVENT_LBUTTONDOWN:
            for i, roi in enumerate(self.rois):
                if x >= roi[0] and x <= roi[0] + roi[2] and y >= roi[1] and y <= roi[1] + roi[3]:
                    self.selected_roi = roi
                    self.dragging = True
                    break

            if self.selected_roi is None:
                # Create a new ROI with initial position
                self.selected_roi = [x, y, 0, 0]
                self.dragging = True

        elif event == cv2.EVENT_MOUSEMOVE and self.dragging:
            self.selected_roi[2] = x - self.selected_roi[0]
            self.selected_roi[3] = y - self.selected_roi[1]

        elif event == cv2.EVENT_LBUTTONUP and self.dragging:
            self.dragging = False
            if self.selected_roi[2] < 0:
                self.selected_roi[0] += self.selected_roi[2]
                self.selected_roi[2] = abs(self.selected_roi[2])
            if self.selected_roi[3] < 0:
                self.selected_roi[1] += self.selected_roi[3]
                self.selected_roi[3] = abs(self.selected_roi[3])
            self.rois.append(self.selected_roi)
            self.selected_roi = None

    def update_trackbar_values(self):
        for i, roi in enumerate(self.rois):
            cv2.createTrackbar(
                f'X Position {i}',
                'Text Recognition',
                roi[0],
                self.video_capture.width,
                lambda val, i=i: self.on_roi_position_change(val, i),
            )
            cv2.createTrackbar(
                f'Y Position {i}',
                'Text Recognition',
                roi[1],
                self.video_capture.height,
                lambda val, i=i: self.on_roi_position_change(val, i),
            )
            cv2.createTrackbar(
                f'Width {i}',
                'Text Recognition',
                roi[2],
                self.video_capture.width,
                lambda val, i=i: self.on_roi_size_change(val, i),
            )
            cv2.createTrackbar(
                f'Height {i}',
                'Text Recognition',
                roi[3],
                self.video_capture.height,
                lambda val, i=i: self.on_roi_size_change(val, i),
            )

    def on_roi_position_change(self, val, index):
        self.rois[index][0] = val

    def on_roi_size_change(self, val, index):
        self.rois[index][2] = val

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
