const canvas = document.getElementById('canvas');
const context = canvas.getContext('2d');
canvas.width = 640; // Ajuste para a largura do seu stream
canvas.height = 480; // Ajuste para a altura do seu stream

let isDrawing = false;
let x = 0;
let y = 0;
let rois = [];
let deletedROIs = [];

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
    rois.push({x1: x, y1: y, x2: e.offsetX, y2: e.offsetY});
    drawRectangle(x, y, e.offsetX, e.offsetY, false);
    isDrawing = false;
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
  rois.forEach(roi => {
    context.beginPath();
    context.rect(roi.x1, roi.y1, roi.x2 - roi.x1, roi.y2 - roi.y1);
    context.strokeStyle = 'red';
    context.lineWidth = 2;
    context.stroke();
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
