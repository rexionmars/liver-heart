#include <iostream>
#include <curl/curl.h>


size_t WriteCallBack(void* contens, size_t size, size_t nmemb, std::string* response);


int main(int argc, char* argv[])
{
    CURL* curl;
    CURLcode res;
    std::string url = "http://127.0.0.1:5000/get-detected-words";

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        // Define a URL da API
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Define a função de callback para escrever o conteúdo da resposta
        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Faz a solicitação HTTP
        res = curl_easy_perform(curl);

        // Faz a busca por erros
        if (res != CURLE_OK) {
            std::cerr << "Erro ao fazer a solicatação HTTP:\n" << curl_easy_strerror(res) << std::endl;
        } else {
            // Mostra a resposta da API
            std::cout << "Response" << std::endl;
            std::cout << response << std::endl;
        }

        // Limpa e finaliza
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Erro ao inicializar o CURL" << std::endl;
    }

    curl_global_cleanup();
    return 0;
}

size_t WriteCallBack(void* contens, size_t size, size_t nmemb, std::string* response)
{
    size_t totalSize = size * nmemb;
    response->append((char*)contens, totalSize);
    return totalSize;
}
