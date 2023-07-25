from flask import Flask, render_template, Response, request
import cv2
import OCR
import threading

app = Flask(__name__)

# Variáveis globais para o OCR e streaming
video_stream = None
ocr = None

def generate_frames():
    global video_stream, ocr
    while True:
        frame = video_stream.frame

        # Faz a detecção OCR no frame
        text = OCR.put_ocr_boxes(ocr.boxes, frame, video_stream.height,
                                 crop_width=ocr.crop_width, crop_height=ocr.crop_height, view_mode=ocr.view_mode)[1]

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

    return 'OCR started successfully.'

@app.route('/video_feed')
def video_feed():
    return Response(generate_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == '__main__':
    app.run(debug=True)
