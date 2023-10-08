import cv2
import easyocr
import threading

# Inicialize o EasyOCR
reader = easyocr.Reader(['en'])

# URL da câmera de entrada
url = 'http://192.168.0.51:81/stream'

# Inicialize o objeto de captura de vídeo
cap = cv2.VideoCapture(url)

# Variável para armazenar o último frame processado
last_frame = None

# Variáveis para definir a zona de captura inicial
x_position = 200
y_position = 200
crop_width = 200
crop_height = 200

# Função para ler texto em um frame
def read_text(frame):
    global last_frame

    # Certifique-se de que a captura de vídeo foi bem-sucedida
    if frame is None:
        return

    # Aplique a zona de captura no frame
    cropped_frame = frame[y_position:y_position + crop_height, x_position:x_position + crop_width]

    # Realize a detecção de texto usando o EasyOCR
    results = reader.readtext(cropped_frame)

    for (bbox, text, prob) in results:
        (top_left, top_right, bottom_right, bottom_left) = bbox
        top_left = tuple(map(int, top_left))
        bottom_right = tuple(map(int, bottom_right))

        # Ajuste as coordenadas da caixa delimitadora para o frame original
        top_left = (top_left[0] + x_position, top_left[1] + y_position)
        bottom_right = (bottom_right[0] + x_position, bottom_right[1] + y_position)

        # Desenhe a caixa delimitadora e o texto reconhecido na imagem original
        cv2.rectangle(frame, top_left, bottom_right, (0, 255, 0), 1)
        cv2.putText(frame, text, (top_left[0], top_left[1] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 0), 1)
        print(f"Text: {text} Prob: {prob}")

    # Desenhe o retângulo de corte
    cv2.rectangle(frame, (x_position, y_position), (x_position + crop_width, y_position + crop_height), (0, 0, 255), 1)

    # Atualize o último frame processado
    last_frame = frame

# Função para processar o vídeo em segundo plano
def video_processing_thread():
    while True:
        # Leia o próximo frame
        ret, frame = cap.read()

        # Chame a função de reconhecimento de texto
        read_text(frame)

# Inicie a thread de processamento de vídeo
video_thread = threading.Thread(target=video_processing_thread)
video_thread.start()

# Crie a janela para exibir a imagem e as trackbars
cv2.namedWindow('Text Recognition')
cv2.createTrackbar('X Position', 'Text Recognition', x_position, 640, lambda x: None)
cv2.createTrackbar('Y Position', 'Text Recognition', y_position, 480, lambda x: None)
cv2.createTrackbar('Crop Width', 'Text Recognition', crop_width, 640, lambda x: None)
cv2.createTrackbar('Crop Height', 'Text Recognition', crop_height, 480, lambda x: None)

while True:
    # Obtenha os valores das trackbars
    x_position = cv2.getTrackbarPos('X Position', 'Text Recognition')
    y_position = cv2.getTrackbarPos('Y Position', 'Text Recognition')
    crop_width = cv2.getTrackbarPos('Crop Width', 'Text Recognition')
    crop_height = cv2.getTrackbarPos('Crop Height', 'Text Recognition')

    # Exiba o último frame processado
    if last_frame is not None:
        cv2.imshow('Text Recognition', last_frame)

    # Saia do loop quando pressionar 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Libere os recursos
cap.release()
cv2.destroyAllWindows()
