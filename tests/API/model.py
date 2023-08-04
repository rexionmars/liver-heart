import json
from flask import Flask, jsonify

app = Flask(__name__)


ECG = 80  # Heart rate
RESP = 14  # Resparation rate
SPO2 = 99  # Oxygen saturation (%)
CO2 = 38  # Carbon dioxide
IBP = "120/80"  # Ivansive Blood Presure
NIMP = "120/80"  # Non-invasive Blood Presure


signals: dict = {
    "ECG bpm": ECG,
    "RESP": RESP,
    "SPO2": SPO2,
    "CO2": CO2,
    "IBP": IBP,
    "NIMP": NIMP
}


@app.route('/monitor')
def api():
    response = json.dumps(signals, indent=4)
    print(response)

    return jsonify(signals), 200


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
