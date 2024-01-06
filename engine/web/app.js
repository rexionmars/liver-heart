const canvas = document.getElementById('canvas');
const context = canvas.getContext('2d');
canvas.width = 640; // ajuste para a largura do seu stream
canvas.height = 480; // ajuste para a altura do seu stream

let isDrawing = false;
let x = 0;
let y = 0;

canvas.addEventListener('mousedown', e => {
  x = e.offsetX;
  y = e.offsetY;
  isDrawing = true;
});

canvas.addEventListener('mousemove', e => {
  if (isDrawing === true) {
    drawRectangle(x, y, e.offsetX, e.offsetY);
  }
});

window.addEventListener('mouseup', e => {
  if (isDrawing === true) {
    drawRectangle(x, y, e.offsetX, e.offsetY);
    x = 0;
    y = 0;
    isDrawing = false;
  }
});

function drawRectangle(x1, y1, x2, y2) {
  context.clearRect(0, 0, canvas.width, canvas.height);
  context.beginPath();
  context.rect(x1, y1, x2 - x1, y2 - y1);
  context.strokeStyle = 'red'; // cor da linha do ROI
  context.lineWidth = 2; // largura da linha do ROI
  context.stroke();
}
