import cv2
import numpy as np
import pywt

# Parâmetros iniciais
camera_url = "http://192.168.0.51:81/stream"
resolution = (640, 480)

# Inicialização do vídeo
cap = cv2.VideoCapture(camera_url)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, resolution[0])
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, resolution[1])

# Função de callback para trackbar
def update_region_size(val):
    global region_size
    region_size = val

# Crie uma janela para a trackbar
cv2.namedWindow('Configuracao')
region_size = 100  # Tamanho inicial da região de captura
cv2.createTrackbar('Tamanho da Região', 'Configuracao', region_size, 300, update_region_size)

while True:
    # Captura um frame
    ret, frame = cap.read()
    if not ret:
        break

    # Obtém a região de interesse
    roi = frame[100:100+region_size, 100:100+region_size]

    # Aplica a transformada wavelet
    coeffs = pywt.dwt2(cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY), 'haar')

    # Mostra as informações no terminal
    print("Approximation (LL):")
    print(coeffs[0])
    print("Horizontal Detail (HL):")
    print(coeffs[1])

    # Verifique se a componente Vertical Detail (LH) está presente
    if len(coeffs) > 2:
        print("Vertical Detail (LH):")
        print(coeffs[2])

    # Diagonal Detail (HH) - Não estamos utilizando, então não vamos imprimir

    # Desenha a forma geométrica
    cv2.rectangle(frame, (100, 100), (100 + region_size, 100 + region_size), (0, 255, 0), 2)

    # Exibe o frame com a região de captura
    cv2.imshow('Frame', frame)

    # Sai do loop se a tecla 'q' for pressionada
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Libera os recursos
cap.release()
cv2.destroyAllWindows()
