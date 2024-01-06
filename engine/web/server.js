const express = require('express');
const { createProxyMiddleware } = require('http-proxy-middleware');
const cors = require('cors');

const app = express();

app.use(cors());

app.use('/camera-stream', createProxyMiddleware({
    target: 'http://192.168.0.51:81',
    changeOrigin: true,
    pathRewrite: {
        '^/camera-stream': '/stream', // O caminho é reescrito para /stream
    },
    // Pode ser necessário incluir mais configurações de CORS aqui dependendo do setup da sua câmera
}));

const PORT = 3000;
app.listen(PORT, () => {
    console.log(`Proxy server running on port ${PORT}`);
});
