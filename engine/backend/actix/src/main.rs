// AuRA
// 2023 - Leonardi Melo

use actix_web::{web, App, HttpResponse, HttpServer, Responder, Error};
use std::sync::{Arc, Mutex};
use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize, Clone)]
struct ROI {
    id: i32,
    coordinates: Coordinates,
}

#[derive(Debug, Serialize, Deserialize, Clone)]
struct Coordinates {
    x1: f64,
    y1: f64,
    x2: f64,
    y2: f64,
}

struct AppState {
    //received_data: Arc<Mutex<Option<serde_json::Value>>>,
    received_data: Arc<Mutex<Option<Vec<ROI>>>>,
}

// ROIS
async fn receive_roi_data(data: web::Json<Vec<ROI>>, app_state: web::Data<AppState>) -> impl Responder {
    let mut received_data = app_state.received_data.lock().unwrap();
    *received_data = Some(data.0.clone());

    HttpResponse::Ok().body("Dados dos ROIs recebidos com sucesso!")
}

// Adiciona uma rota para enviar os dados dos ROIs
async fn get_roi_data(app_state: web::Data<AppState>) -> Result<HttpResponse, Error> {
    let received_data = app_state.received_data.lock().unwrap();

    match &*received_data {
        Some(data) => {
            let json_string = serde_json::to_string(data).unwrap();
            Ok(HttpResponse::Ok()
                .content_type("application/json")
                .body(json_string))
        },
        None => {
            Ok(HttpResponse::NotFound().body("Nenhum dado de ROI recebido ainda."))
        }
    }
}


async fn receive_data(data: web::Json<Vec<ROI>>, app_state: web::Data<AppState>) -> impl Responder {
    let mut received_data = app_state.received_data.lock().unwrap();
    *received_data = Some(data.into_inner()); // Não precisa clonar, pois Json implementa IntoInner

    // Envia uma resposta de sucesso (200 OK) para a solicitação POST
    HttpResponse::Ok()
        .body("Dados recebidos com sucesso!")
}


async fn get_received_data(app_state: web::Data<AppState>) -> Result<HttpResponse, Error> {
    let received_data = app_state.received_data.lock().unwrap();

    match &*received_data {
        Some(rois) => {
            // Converte a lista de ROIs para JSON
            let json_string = serde_json::to_string(rois).unwrap();
            
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
            .service(web::resource("/receive_roi_data").route(web::post().to(receive_roi_data)))
            .service(web::resource("/get_roi_data").route(web::get().to(get_roi_data)))
            .service(web::resource("/receive_data").route(web::post().to(receive_data)))
            .service(web::resource("/get_received_data").route(web::get().to(get_received_data)))
    })
    .bind("127.0.0.1:8080")?
    .run()
    .await
}
