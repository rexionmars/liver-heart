const canvas = document.getElementById('canvas');
const context = canvas.getContext('2d');
canvas.width = 640; // Ajuste para a largura do seu stream
canvas.height = 480; // Ajuste para a altura do seu stream

let isDrawing = false;
let x = 0;
let y = 0;
let rois = [];
let deletedROIs = [];
let currentId = 0; // Inicializa o contador de ID

canvas.addEventListener('mousedown', e => {
  x = e.offsetX;
  y = e.offsetY;
  isDrawing = true;
});

canvas.addEventListener('mousemove', e => {
  if (isDrawing === true) {
    drawRectangle(x, y, e.offsetX, e.offsetY, true);
  }
});

canvas.addEventListener('mouseup', e => {
  if (isDrawing === true) {
    // Estrutura original que seu código espera
    const newROI = {
      id: currentId++,
      x1: x,
      y1: y,
      x2: e.offsetX,
      y2: e.offsetY
    };
    rois.push(newROI);
    isDrawing = false;
    drawAllROIs(); // Desenha todos os ROIs
  }
});

document.addEventListener('keydown', e => {
  if (e.key === 'd') {
    deleteLastROI();
  } else if (e.key === 'r') {
    recoverLastROI();
  }
});

function drawRectangle(x1, y1, x2, y2, isTemporary) {
  if (isTemporary) {
    context.clearRect(0, 0, canvas.width, canvas.height);
    drawAllROIs();
  }
  context.beginPath();
  context.rect(x1, y1, x2 - x1, y2 - y1);
  context.strokeStyle = 'red';
  context.lineWidth = 2;
  context.stroke();
  if (!isTemporary) {
    context.save();
  }
}

function drawAllROIs() {
  context.clearRect(0, 0, canvas.width, canvas.height); // Limpa o canvas antes de desenhar
  rois.forEach(roi => {
    context.beginPath();
    context.rect(roi.x1, roi.y1, roi.x2 - roi.x1, roi.y2 - roi.y1);
    context.strokeStyle = 'red';
    context.lineWidth = 2;
    context.stroke();
    context.fillStyle = 'white'; // Define a cor do texto para garantir visibilidade
    context.font = '12px Arial'; // Define o tamanho e a fonte do texto
    context.fillText(`ID: ${roi.id}`, roi.x1, roi.y1 - 5); // Ajuste a posição conforme necessário
  });
}


function deleteLastROI() {
  if (rois.length > 0) {
    deletedROIs.push(rois.pop());
    redrawROIs();
  }
}

function recoverLastROI() {
  if (deletedROIs.length > 0) {
    rois.push(deletedROIs.pop());
    redrawROIs();
  }
}

function redrawROIs() {
  context.clearRect(0, 0, canvas.width, canvas.height);
  drawAllROIs();
}


function sendROIsToServer() {
  const url = 'http://example.com/api/rois'; // Substitua pela URL do seu servidor

  // Transforma os ROIs em um formato adequado para envio
  const dataToSend = rois.map(roi => {
    return {
      id: roi.id,
      coordinates: {
        x1: roi.x1,
        y1: roi.y1,
        x2: roi.x2,
        y2: roi.y2
      }
    };
  });

  // Serializa os dados para JSON
  const data = JSON.stringify(dataToSend);

  // Usa a API fetch para enviar os dados via POST
  fetch(url, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json'
    },
    body: data
  })
  .then(response => {
    if (!response.ok) {
      throw new Error(`HTTP error! status: ${response.status}`);
    }
    return response.json();
  })
  .then(data => {
    console.log('Success:', data);
  })
  .catch((error) => {
    console.error('Error:', error);
  });
}

sendROIsToServer();