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

// Evento mouseup atualizado para usar as coordenadas atuais diretamente
canvas.addEventListener('mouseup', e => {
  if (isDrawing === true) {
    const roi = {
      id: currentId++, // Incrementa o ID para cada novo ROI
      x1: x, // Usa a variável 'x' que foi definida no evento mousedown
      y1: y, // Usa a variável 'y' que foi definida no evento mousedown
      x2: e.offsetX, // Usa as coordenadas do evento
      y2: e.offsetY  // Usa as coordenadas do evento
    };
    rois.push(roi); // Atualiza a lista de ROIs
    isDrawing = false;
    drawAllROIs(); // Desenha todos os ROIs
    onROIDrawn(roi); // Chama a função para enviar o ROI ao servidor
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

function onROIDrawn(roi) {
  // Log da lista de ROIs para depuração
  console.log('ROIs atuais:', rois);
  // Envio do ROI ao servidor
  sendROIToServer(roi); 
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


function sendROIToServer(roi) {
  const url = 'http://127.0.0.1:8080/receive_roi_data';
  
  // Cria um vetor com um único ROI
  const dataToSend = [{
    id: roi.id,
    coordinates: {
      x1: roi.x1,
      y1: roi.y1,
      x2: roi.x2,
      y2: roi.y2
    }
  }];

  console.log('Printa Data:', JSON.stringify(dataToSend));

  const data = JSON.stringify(dataToSend);

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
    return response.text();
  })
  .then(responseText => {
    console.log('Resposta do servidor:', responseText);
  })
  .catch((error) => {
    console.error('Erro ao enviar ROI:', error);
  });
}


// Agora você precisa garantir que a função onROIDrawn é chamada sempre que um ROI é desenhado
// Por exemplo, dentro do seu evento mouseup após a criação do ROI:
canvas.addEventListener('mouseup', e => {
  if (isDrawing === true) {
    const roi = {
      id: generateUniqueID(), // Implemente uma função para gerar um ID único
      x1: startPoint.x,
      y1: startPoint.y,
      x2: e.offsetX,
      y2: e.offsetY
    };
    rois.push(roi);  // Atualiza a lista de ROIs (se ainda precisar dela para outros propósitos)
    isDrawing = false;
    onROIDrawn(roi);  // Chama a função para enviar o ROI ao servidor
  }
});
