import cv2
import easyocr
import threading

class TextRecognition:
    def __init__(self, video_source, language="en"):
        self.reader = easyocr.Reader([language])
        self.video_capture = cv2.VideoCapture(video_source)
        self.last_frame = None
        self.rois = []  # Lista para armazenar as ROIs
        self.current_roi = None  # A ROI atualmente sendo criada
        self.drawing = False  # Flag para indicar se estamos desenhando uma ROI

    def start(self):
        video_thread = threading.Thread(target=self.video_processing_thread)
        video_thread.start()
        self.display_window()

    def read_text(self, frame):
        if frame is None:
            return

        for roi in self.rois:
            x, y, w, h = roi
            cropped_frame = frame[y:y + h, x:x + w]
            results = self.reader.readtext(cropped_frame)

            for bbox, text, prob in results:
                (top_left, top_right, bottom_right, bottom_left) = bbox
                top_left = tuple(map(int, top_left))
                bottom_right = tuple(map(int, bottom_right))

                top_left = (top_left[0] + x, top_left[1] + y)
                bottom_right = (
                    bottom_right[0] + x,
                    bottom_right[1] + y,
                )

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

        for roi in self.rois:
            x, y, w, h = roi
            cv2.rectangle(
                frame,
                (x, y),
                (x + w, y + h),
                (0, 0, 255),
                1,
            )

        if self.current_roi is not None:
            x, y, w, h = self.current_roi
            cv2.rectangle(
                frame,
                (x, y),
                (x + w, y + h),
                (0, 255, 0),
                1,
            )

        self.last_frame = frame

    def video_processing_thread(self):
        while True:
            ret, frame = self.video_capture.read()
            self.read_text(frame)

    def display_window(self):
        cv2.namedWindow("Text Recognition")
        cv2.setMouseCallback("Text Recognition", self.on_mouse_events)

        while True:
            if self.last_frame is not None:
                cv2.imshow("Text Recognition", self.last_frame)

            if cv2.waitKey(1) & 0xFF == ord("q"):
                break

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

if __name__ == "__main__":
    text_recognition = TextRecognition("http://192.168.0.51:81/stream")
    text_recognition.start()