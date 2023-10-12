from flask import Flask, render_template, Response
from EASY.text_recognition_module import TextRecognition

app = Flask(__name)
text_recognition = TextRecognition("http://192.168.0.51:81/stream")

@app.route('/')
def index():
    return render_template('index.html')  # Create an HTML template for your web interface

def generate():
    while text_recognition.running:
        frame = text_recognition.last_frame
        if frame is not None:
            _, jpeg = cv2.imencode('.jpg', frame)
            frame_bytes = jpeg.tobytes()
            yield (b'--frame\r\n' b'Content-Type: image/jpeg\r\n\r\n' + frame_bytes + b'\r\n')

@app.route('/video_feed')
def video_feed():
    return Response(generate(), mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == "__main__":
    app.run(host='0.0.0.0', debug=True)  # Run the Flask app on your server
