import cv2
import time
import pytesseract

path = "../media_train/img/7.png"
setting = '--oem 2 --psm 6 outputbase digits'

img = cv2.imread(path)
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

def detect_characters():
    height_img, width_img, _ = img.shape
    boxes = pytesseract.image_to_boxes(img, config=setting)

    for box_ch in boxes.splitlines():
        box_ch = box_ch.split(' ')
        print(box_ch)
        x, y, w, h = int(box_ch[1]), int(box_ch[2]), int(box_ch[3]), int(box_ch[4])
        cv2.rectangle(img, (x, height_img - y), (w, height_img - h), (36, 197, 255), 1)
        cv2.putText(img, box_ch[0], (x, height_img + 25), cv2.FONT_HERSHEY_COMPLEX, 1, (36, 197, 255), 1)

    cv2.imshow('Show', img)

def detect_words():
    height_img, width_img, _ = img.shape
    boxes = pytesseract.image_to_data(img)
    #print(boxes)

    for x, box_ch in enumerate(boxes.splitlines()):
        if x != 0:
            box_ch = box_ch.split()
            print(box_ch)

            if len(box_ch) == 12:
                x, y, w, h = int(box_ch[6]), int(box_ch[7]), int(box_ch[8]), int(box_ch[9])
                cv2.rectangle(img, (x,y), (w+x, h+y), (36, 197, 255), 1)
                cv2.putText(img, box_ch[11], (x, y), cv2.FONT_HERSHEY_COMPLEX, 0.5, (36, 197, 255), 1)

    cv2.imshow('Show', img)

def detect_only_digit():
    height_img, width_img, _ = img.shape
    boxes = pytesseract.image_to_data(img, config=setting)
    #print(boxes)

    for x, box_ch in enumerate(boxes.splitlines()):
        if x != 0:
            box_ch = box_ch.split()
            print(box_ch)

            if len(box_ch) == 12:
                x, y, w, h = int(box_ch[6]), int(box_ch[7]), int(box_ch[8]), int(box_ch[9])
                cv2.rectangle(img, (x,y), (w+x, h+y), (36, 197, 255), 1)
                cv2.putText(img, box_ch[11], (x, y), cv2.FONT_HERSHEY_COMPLEX, 0.5, (36, 197, 255), 1)

    cv2.imshow('Show', img)

detect_characters()

while True:
    key = cv2.waitKey(0)

    if key == 27:
        break
    if key != -1:
        continue

cv2.destroyAllWindows()
