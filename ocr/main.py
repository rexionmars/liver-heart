import cv2
import time
import pytesseract

path = "../media_train/img/8.png"

img = cv2.imread(path)
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

#print(pytesseract.image_to_string(img))

# Detecting characters
#print(pytesseract.image_to_boxes(img))

def detect_characters():
    height_img, width_img, _ = img.shape
    boxes = pytesseract.image_to_boxes(img)

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
    print(boxes)

    for x, box_ch in enumerate(boxes.splitlines()):
        if x != 0:
            box_ch = box_ch.split()
            print(box_ch)
            #x, y, w, h = int(box_ch[1]), int(box_ch[2]), int(box_ch[3]), int(box_ch[4])
            #cv2.rectangle(img, (x, height_img - y), (w, height_img - h), (36, 197, 255), 1)
            #cv2.putText(img, box_ch[0], (x, height_img + 25), cv2.FONT_HERSHEY_COMPLEX, 1, (36, 197, 255), 1)

    cv2.imshow('Show', img)

detect_words()

while True:
    # Espera por uma tecla ser pressionada
    key = cv2.waitKey(0)

    if key == 27:
        break
    # Verifica se uma tecla foi pressionada
    if key != -1:
        # Adicione aqui o código para evitar o fechamento da janela
        # Por exemplo, você pode exibir uma mensagem ou executar uma ação específica
        continue

    # A janela será fechada quando nenhuma tecla for pressionada

# Fecha a janela
cv2.destroyAllWindows()
