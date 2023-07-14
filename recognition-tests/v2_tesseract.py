import cv2
import pytesseract

img_path = '../media_train/img/8.png'

setting = '--oem 2 --psm 6 outputbase digits'

img = cv2.imread(img_path)

cv2.imshow('Window', img)

while True:
    key = cv2.waitKey(0)
    if key == 27:
        break
    if key != -1:
        continue

cv2.destroyAllWindows()
