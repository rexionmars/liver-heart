import cv2



# URL do fluxo de vídeo da câmera
video_url = "http://192.168.0.51:81/stream"

# Inicializa o objeto de captura de vídeo
cap = cv2.VideoCapture(video_url)

# Função de callback para o evento de clique e arraste do mouse
def draw_roi(event, x, y, flags, param):
    global roi_points, roi_selected, roi_completed

    if event == cv2.EVENT_LBUTTONDOWN:
        roi_points = [(x, y)]
        roi_selected = True
        roi_completed = False
    elif event == cv2.EVENT_MOUSEMOVE:
        if roi_selected and not roi_completed:
            roi_points.append((x, y))
    elif event == cv2.EVENT_LBUTTONUP:
        roi_selected = False
        roi_completed = True

# Inicializa variáveis para ROI
roi_points = []
roi_selected = False
roi_completed = False

# Configura a janela e associa a função de callback
cv2.namedWindow("Video Stream")
cv2.setMouseCallback("Video Stream", draw_roi)

# Loop principal para captura e processamento de vídeo
while True:
    ret, frame = cap.read()

    if not ret:
        break

    # Desenha a ROI durante o clique e arraste
    if roi_selected and not roi_completed:
        for i in range(len(roi_points) - 1):
            cv2.line(frame, roi_points[i], roi_points[i + 1], (0, 255, 0), 2)

    cv2.imshow("Video Stream", frame)

    # Encerra o loop quando a tecla 'q' é pressionada
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Libera os recursos e fecha a janela
cap.release()
cv2.destroyAllWindows()


    def read_text(self, frame):
        if frame is None:
            return

        roi_data = {}  # Dictionary to store ROI data

        for i, roi in enumerate(self.rois):
            x, y, w, h = roi
            cropped_frame = frame[y : y + h, x : x + w]
            results = self.reader.readtext(cropped_frame)

            roi_info = {}  # Dictionary to store current ROI information

            list_value = []
            for bbox, text, prob in results:
                label, value = self.extract_label_and_value(text)
                list_value.append(value)

                if label:
                    if label in roi_info:
                        roi_info[label].append(value)
                    else:
                        roi_info[label] = [value]

                # Render text detection on the frame within the ROI
                text_x = x + bbox[0][0]
                text_y = y + bbox[0][1]
                cv2.rectangle(
                    frame,
                    (text_x, text_y),
                    (x + bbox[2][0], y + bbox[2][1]),
                    (0, 255, 0),
                    1,
                )
                cv2.putText(
                    frame,
                    text,
                    (text_x, text_y - 10),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.5,
                    (0, 255, 0),
                    1,
                )

            # Process list value
            list_value.pop(0) # Dropout of first element in list(None)
            new_values = [int(item) for item in list_value]

            print(label)
            print(f"label: {label}, len: {len(new_values)}, content: {new_values}")
            roi_data[f"ROI_ID {i}"] = roi_info
