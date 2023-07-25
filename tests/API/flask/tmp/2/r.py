import requests

data = {
    "source": 0,
    "crop": [200, 200],
    "view_mode": 1,
    "language": "eng"  # Substitua 'por' pelo código da linguagem desejada
}

response = requests.post('http://127.0.0.1:5000/ocr', json=data)

print(response.json())
