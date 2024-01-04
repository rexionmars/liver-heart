let video = document.getElementById("videoInput");
let canvas = document.getElementById("canvasOutput");
let context = canvas.getContext("2d");

// Inicializa a captura de vídeo
navigator.mediaDevices.getUserMedia({ video: true, audio: false })
    .then(function(stream) {
        video.srcObject = stream;
        video.play();
    })
    .catch(function(err) {
        console.log("An error occurred! " + err);
    });

let src = new cv.Mat(video.height, video.width, cv.CV_8UC4);
let dst = new cv.Mat(video.height, video.width, cv.CV_8UC1);

// Processa a imagem quando o OpenCV estiver pronto
cv['onRuntimeInitialized'] = function() {
    processVideo();
};

function processVideo() {
    if (video.readyState === video.HAVE_ENOUGH_DATA) {
        // Desenha o frame do vídeo no canvas
        context.drawImage(video, 0, 0, video.width, video.height);

        // Converte o frame para uma imagem Mat do OpenCV
        src.data.set(context.getImageData(0, 0, video.width, video.height).data);

        // Aplica o filtro Canny
        cv.cvtColor(src, dst, cv.COLOR_RGBA2GRAY);
        cv.Canny(dst, dst, 50, 100, 3, false);

        // Exibe a imagem resultante
        cv.imshow("canvasOutput", dst);
    }

    // Continua processando frames
    requestAnimationFrame(processVideo);
}
