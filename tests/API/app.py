import os
import sys
import cv2
import threading

from optical_character_recog import OCR

from flask import Flask, render_template, Response, request, jsonify
from flask_socketio import SocketIO, emit

app = Flask(__name__)
app.config['SECRET_KEY'] = 'a1b2c3d4e5f6g7h8i9j0k1l2m3n4o5p6'
socketio = SocketIO(app)

# Variáveis globais para o OCR e streaming
video_stream = None
ocr = None
# Variável global para armazenar as palavras detectadas
detected_words = []

def generate_frames():
    global video_stream, ocr
    while True:
        if video_stream is not None and ocr is not None:
            frame = video_stream.frame

            # Faz a detecção OCR no frame
            _, text = OCR.put_ocr_boxes(ocr.boxes, frame, frame.shape[0],
                                        crop_width=ocr.crop_width, crop_height=ocr.crop_height, view_mode=ocr.view_mode)

            # Emitir as palavras detectadas para os clientes conectados através do WebSocket
            socketio.emit('detected_words', {'words': text.split()})

            ret, buffer = cv2.imencode('.jpg', frame)
            frame = buffer.tobytes()
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')


@app.route('/')
def index():
    return render_template('index.html')

@app.route('/start_ocr', methods=['POST'])
def start_ocr():
    global video_stream, ocr

    data = request.form
    source = int(data['source'])
    crop = [int(data['crop_width']), int(data['crop_height'])]
    view_mode = int(data['view_mode'])
    language = data['language']

    video_stream = OCR.VideoStream(source).start()
    img_wi, img_hi = video_stream.get_video_dimensions()

    ocr = OCR.OCR().start()
    ocr.set_exchange(video_stream)
    ocr.set_language(language)
    ocr.set_dimensions(img_wi, img_hi, crop[0], crop[1])
    ocr.view_mode = view_mode  # Adiciona o atributo view_mode à classe OCR

    return 'OCR started successfully.'

@app.route('/video_feed')
def video_feed():
    return Response(generate_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/get_detected_words')
def get_detected_words():
    global detected_words
    return jsonify({'words': detected_words})

@app.route('/detected_words')
def show_detected_words():
    return render_template('detected_words.html')

@app.route('/client')
def serve_client():
    return app.send_static_file('client.html')


if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5000)