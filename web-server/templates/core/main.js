const video = document.getElementById('videoElement');
const canvas = document.getElementById('canvas');
const context = canvas.getContext('2d');
const startStopButton = document.getElementById('startStopButton');
let isDrawing = false;
let rois = [];
let isRecognitionRunning = false;

const constraints = {
    video: true
};

// Get user media and display the video stream
navigator.mediaDevices.getUserMedia(constraints)
    .then(function (stream) {
        video.srcObject = stream;
    })
    .catch(function (error) {
        console.error('Error accessing the camera:', error);
    });

// Start/Stop text recognition
startStopButton.addEventListener('click', function () {
    if (!isRecognitionRunning) {
        startStopButton.innerText = 'Stop';
        isRecognitionRunning = true;
        // Use JavaScript to make a request to your Flask endpoint to start text recognition
        // Example: fetch('/start_recognition');
    } else {
        startStopButton.innerText = 'Start';
        isRecognitionRunning = false;
        // Use JavaScript to make a request to your Flask endpoint to stop text recognition
        // Example: fetch('/stop_recognition');
    }
});

// Event listener for mouse down
canvas.addEventListener('mousedown', function (e) {
    isDrawing = true;
    const rect = canvas.getBoundingClientRect();
    const x = e.clientX - rect.left;
    const y = e.clientY - rect.top;
    rois.push([x, y, 0, 0]);
});

// Event listener for mouse move (while drawing)
canvas.addEventListener('mousemove', function (e) {
    if (!isDrawing) return;
    const rect = canvas.getBoundingClientRect();
    const x = e.clientX - rect.left;
    const y = e.clientY - rect.top;
    const roi = rois[rois.length - 1];
    roi[2] = x - roi[0];
    roi[3] = y - roi[1];
    drawRois();
});

// Event listener for mouse up
canvas.addEventListener('mouseup', function () {
    isDrawing = false;
});

function drawRois() {
    context.clearRect(0, 0, canvas.width, canvas.height);
    context.strokeStyle = 'red';
    context.lineWidth = 2;
    for (const roi of rois) {
        context.strokeRect(roi[0], roi[1], roi[2], roi[3]);
    }
}

// Periodically request recognition results from the server
function getRecognitionResults() {
    if (isRecognitionRunning) {
        // Use JavaScript to make a request to your Flask endpoint to get recognition results
        // Example: fetch('/get_recognition_results')
        // Process the results and display them on the webpage
    }
    setTimeout(getRecognitionResults, 1000); // Poll every 1 second
}

getRecognitionResults();
