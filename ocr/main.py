import cv2
import time
import pytesseract
from pytesseract import Output


from config.ts import TESSERACT_CONFIG

path = "../media_train/img/8.png"

img = cv2.imread(path)
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

def letter_bounding():
    height, width, _ = img.shape
    letter_boxes = pytesseract.image_to_boxes(img)
    print(letter_boxes)

    for box in letter_boxes.splitlines():
        box = box.split()
        print(box)
        x,y,w,h = int(box[1]),int(box[2]),int(box[3]),int(box[4])
        cv2.rectangle(img,(x,height-y),(w,height-h), (0,0,255),1)
        #cv2.putText(COMMON_PUTTEXT)


def detect_characters():
    height, width, _ = img.shape
    boxes = pytesseract.image_to_boxes(img, config=TESSERACT_CONFIG)

    for box_character in boxes.splitlines():
        box_character = box_character.split(' ')
        print(box_character)

        x, y, w, h = int(box_character[1]), int(box_character[2]), int(box_character[3]), int(box_character[4])
        cv2.rectangle(img, (x, height - y), (w, height - h), (36, 197, 255), 1)
        cv2.putText(img, box_character[0], (x, height + 25), cv2.FONT_HERSHEY_COMPLEX, 1, (36, 197, 255), 1)


def detect_words():
    height, width, _ = img.shape
    boxes = pytesseract.image_to_data(img)
    print(boxes)

    for x, box_character in enumerate(boxes.splitlines()):
        if x != 0:
            box_character = box_character.split()
            print(box_character)

            if len(box_character) == 12:
                x, y, w, h = int(box_character[6]), int(box_character[7]), int(box_character[8]), int(box_character[9])
                cv2.rectangle(img, (x,y), (w+x, h+y), (36, 197, 255), 1)
                cv2.putText(img, box_character[11], (x, y), cv2.FONT_HERSHEY_COMPLEX, 0.5, (36, 197, 255), 1)


def detect_only_digit():
    height, width, _ = img.shape
    boxes = pytesseract.image_to_data(img, config=TESSERACT_CONFIG)
    print(boxes)

    for x, box_character in enumerate(boxes.splitlines()):
        if x != 0:
            box_character = box_character.split()
            print(box_character)

            if len(box_character) == 12:
                x, y, w, h = int(box_character[6]), int(box_character[7]), int(box_character[8]), int(box_character[9])
                cv2.rectangle(img, (x,y), (w+x, h+y), (36, 197, 255), 1)
                cv2.putText(img, box_character[11], (x, y), cv2.FONT_HERSHEY_COMPLEX, 0.5, (36, 197, 255), 1)


detect_only_digit()

cv2.imshow('Show', img)

# Use this block code only your use an Window Manager, example: i3wm, hyprland, bspwm
while True:
    key = cv2.waitKey(0)

    if key == 27:
        break
    if key != -1:
        continue

cv2.destroyAllWindows()
