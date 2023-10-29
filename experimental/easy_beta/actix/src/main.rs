use actix_web::{web, App, HttpResponse, HttpServer, Responder, Error};
use std::sync::{Arc, Mutex};

struct AppState {
    received_data: Arc<Mutex<Option<serde_json::Value>>>,
}

async fn receive_data(data: web::Json<serde_json::Value>, app_state: web::Data<AppState>) -> impl Responder {
    let mut received_data = app_state.received_data.lock().unwrap();
    *received_data = Some(data.0.clone());

    // Envia uma resposta de sucesso (200 OK) para a solicitação POST
    HttpResponse::Ok()
        .body("Dados recebidos com sucesso!")
}

async fn get_received_data(app_state: web::Data<AppState>) -> Result<HttpResponse, Error> {
    let received_data = app_state.received_data.lock().unwrap();

    match &*received_data {
        Some(data) => {
            // Converte o JSON para uma string
            let json_string = serde_json::to_string(data).unwrap();
            
            // Envia o JSON como resposta
            Ok(HttpResponse::Ok()
                .content_type("application/json")
                .body(json_string))
        },
        None => {
            // Se nenhum dado foi recebido ainda
            Ok(HttpResponse::NotFound().body("Nenhum dado recebido ainda."))
        }
    }
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    let app_state = web::Data::new(AppState {
        received_data: Arc::new(Mutex::new(None)),
    });

    HttpServer::new(move || {
        App::new()
            .app_data(app_state.clone())
            .service(web::resource("/receive_data").route(web::post().to(receive_data)))
            .service(web::resource("/get_received_data").route(web::get().to(get_received_data)))
    })
    .bind("127.0.0.1:8080")?
    .run()
    .await
}
