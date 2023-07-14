import cv2
import numpy as np
import pytesseract
from pytesseract import Output

from config.general import *

path = "../media_train/m4/4.mp4"

video = cv2.VideoCapture(path)

fps = video.get(cv2.CAP_PROP_FPS)
print(fps)

def main():
    contr = 0

    while True:
        ret, frame = video.read()

        # Control the frame rate
        contr += 1
        if contr % 30 == 0:
            imgH, imgW, _ = frame.shape
            x1, y1, w1, h1 = 0, 0, imgH, imgW

            img_char = pytesseract.image_to_string(frame, config='--psm 6')
            img_boxes = pytesseract.image_to_boxes(frame, config='--psm 6')

            for box in img_boxes.splitlines():
                print(img_char)
                print(img_boxes)

                box = box.split(' ')
                print(box)
                x, y, h, w = int(box[1]), int(box[2]), int(box[3]), int(box[4])
                cv2.rectangle(frame, (x, imgH - y), (w, imgH - h), (0, 120, 255), 1)

            #cv2.rectangle(frame, (x1, x1), (x1 + w1, y1 + h1), (0, 0, 0), -1)
            cv2.putText(frame, img_char, (x1 + int(w1 / 50), y1 + int(h1 / 50)), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)


        cv2.imshow('Test', frame)

        if cv2.waitKey(2) & 0xFF == ord('q'):
            break

    video.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
