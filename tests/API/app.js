// Função para fazer a requisição e obter o JSON
function getJSONFromLocalhost() {
  fetch('http://localhost:5000/get_detected_words')
    .then(response => response.json())
    .then(data => {
      // Aqui você pode manipular os dados obtidos (data)
      console.log(data);
    })
    .catch(error => {
      console.error('Erro ao obter JSON:', error);
    });
}

// Chamar a função para buscar os dados em intervalos regulares (se necessário)
setInterval(getJSONFromLocalhost, 1000); // Buscar a cada 5 segundos, por exemplo
