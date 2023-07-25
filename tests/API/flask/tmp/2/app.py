from flask import Flask, request, jsonify
import OCR

app = Flask(__name__)

@app.route('/ocr', methods=['POST'])
def ocr_api():
    try:
        data = request.get_json()
        source = data.get('source', 0)
        crop = data.get('crop', [0, 0])
        view_mode = data.get('view_mode', 1)
        language = data.get('language', None)

        OCR.ocr_stream(crop=crop, source=source, view_mode=view_mode, language=language)

        return jsonify({"message": "OCR process completed successfully."})

    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)
