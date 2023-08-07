import json
from flask import Flask, jsonify

app = Flask(__name__)


ECG = 80  # Heart rate
RESP = 14  # Resparation rate
SPO2 = 99  # Oxygen saturation (%)
CO2 = 38  # Carbon dioxide

# Ivansive Blood Presure
ART_IBP = "120/80"
ART_MMHG = 93
CVP_IBP = "120/80"
CVP_MMHG = 93

NIMP = "120/80"  # Non-invasive Blood Presure
NIMP_MMHG = 93


signals: dict = {
    "ECG bpm": ECG,
    "RESP": RESP,
    "SpO2": SPO2,
    "Co2": CO2,
    "IBP": {
        "ART": {
            "mmHg": ART_MMHG,
            "sys": ART_IBP,
        },
        "CVP": {
            "mmHg": CVP_MMHG,
            "sys": CVP_IBP,
        },
    },
    "NIMP": {
        "mmHg": NIMP_MMHG,
        "sys": NIMP,
    }
}


@app.route('/monitor')
def api():
    _ = json.dumps(signals, indent=4)
    return jsonify(signals), 200


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
