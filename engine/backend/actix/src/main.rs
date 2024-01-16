// AuRA
// 2023 - Leonardi Melo

use actix_cors::Cors;
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
    
    if let Some(ref mut rois) = *received_data {
        // Se já existem ROIs, os adiciona à lista existente.
        rois.extend(data.0.clone());
    } else {
        // Se ainda não existem ROIs, cria uma nova lista.
        *received_data = Some(data.0.clone());
    }

    HttpResponse::Ok().body("Dados dos ROIs recebidos com sucesso!")
}


// Adiciona uma rota para enviar os dados dos ROIs
async fn get_roi_data(app_state: web::Data<AppState>) -> Result<HttpResponse, Error> {
    let received_data = app_state.received_data.lock().unwrap();

    match &*received_data {
        Some(rois) => {
            // Cria um mapa onde as chaves são os IDs dos ROIs e os valores são as coordenadas
            let roi_map: serde_json::Map<String, serde_json::Value> = rois
                .iter()
                .map(|roi| {
                    (
                        format!("roiID{}", roi.id), // Cria a chave usando o ID do ROI
                        serde_json::json!({
                            "x1": roi.coordinates.x1,
                            "y1": roi.coordinates.y1,
                            "x2": roi.coordinates.x2,
                            "y2": roi.coordinates.y2,
                        }), // Cria o valor com as coordenadas
                    )
                })
                .collect();

            let json_string = serde_json::to_string(&roi_map).unwrap();
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
    env_logger::init();

    let app_state = web::Data::new(AppState {
        received_data: Arc::new(Mutex::new(None)),
    });

    HttpServer::new(move || {
        let cors = Cors::permissive(); // Isso habilita o CORS para todas as origens. Para produção, restrinja as origens!

        App::new()
            .wrap(cors)
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
