use actix_web::{web, App, HttpResponse, HttpServer, Responder};
use serde::{Deserialize, Serialize};
use std::sync::{Mutex, Arc};

// Estrutura de dados para receber dados do OCR
#[derive(Debug, Serialize, Deserialize, Clone)]
struct OcrData {
    // Defina as estruturas de dados conforme a estrutura do JSON que você espera do OCR
    roi_data: String,  // Altere o tipo de acordo com sua estrutura
}

// Estado compartilhado entre as rotas
struct AppState {
    received_data: Mutex<Vec<OcrData>,
}

// Rota para receber dados JSON do OCR
async fn receive_data(data: web::Json<OcrData>, app_state: web::Data<AppState>) -> impl Responder {
    let received_data = &app_state.received_data;
    
    // Bloqueia o Mutex para adicionar os dados recebidos
    let mut received_data = received_data.lock().expect("Falha ao obter o Mutex");
    received_data.push(data.into_inner());

    HttpResponse::Ok().body("Dados recebidos com sucesso!")
}

// Rota para recuperar os dados recebidos
async fn get_received_data(app_state: web::Data<AppState>) -> impl Responder {
    let received_data = &app_state.received_data;
    
    // Bloqueia o Mutex para obter os dados recebidos
    let received_data = received_data.lock().expect("Falha ao obter o Mutex");
    
    if received_data.is_empty() {
        HttpResponse::NotFound().body("Nenhum dado recebido ainda.")
    } else {
        HttpResponse::Ok().json(received_data.clone())
    }
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    // Cria uma instância de estado compartilhado
    let app_state = web::Data::new(AppState {
        received_data: Mutex::new(Vec::new()),
    });
    
    HttpServer::new(move || {
        App::new()
            .app_data(app_state.clone()) // Compartilha o estado com todas as funções
            .service(web::resource("/receive_data").route(web::post().to(receive_data))
            .service(web::resource("/get_received_data").route(web::get().to(get_received_data))
    })
    .bind("127.0.0.1:8080")?
    .run()
    .await
}
