package main

import (
	"encoding/json"
	"log"
	"net/http"
	"sync"
)

type ROI struct {
    ID          int         `json:"id"`
    Coordinates Coordinates `json:"coordinates"`
}

type Coordinates struct {
    X1 float64 `json:"x1"`
    Y1 float64 `json:"y1"`
    X2 float64 `json:"x2"`
    Y2 float64 `json:"y2"`
}

type AppState struct {
    ReceivedData *sync.Mutex
    ROIs         []ROI
}
/*
func receiveROIData(w http.ResponseWriter, r *http.Request, appState *AppState) {
    var rois []ROI
    err := json.NewDecoder(r.Body).Decode(&rois)
    if err != nil {
        http.Error(w, err.Error(), http.StatusBadRequest)
        return
    }

    appState.ReceivedData.Lock()
    defer appState.ReceivedData.Unlock()

    appState.ROIs = append(appState.ROIs, rois...)

    w.WriteHeader(http.StatusOK)
    w.Write([]byte("Dados dos ROIs recebidos com sucesso!"))
}

*/

func receiveROIData(w http.ResponseWriter, r *http.Request, appState *AppState) {
    log.Println("Received request to receive ROI data")

    var rois []ROI
    err := json.NewDecoder(r.Body).Decode(&rois)
    if err != nil {
        log.Println("Error decoding ROI data:", err)
        http.Error(w, err.Error(), http.StatusBadRequest)
        return
    }

    appState.ReceivedData.Lock()
    defer appState.ReceivedData.Unlock()

    appState.ROIs = append(appState.ROIs, rois...)

    log.Println("ROI data received successfully")

    w.WriteHeader(http.StatusOK)
    w.Write([]byte("Dados dos ROIs recebidos com sucesso!"))
}


func getROIData(w http.ResponseWriter, r *http.Request, appState *AppState) {
    appState.ReceivedData.Lock()
    defer appState.ReceivedData.Unlock()

    if len(appState.ROIs) == 0 {
        http.Error(w, "Nenhum dado de ROI recebido ainda.", http.StatusNotFound)
        return
    }

    roiMap := make(map[string]interface{})
    for _, roi := range appState.ROIs {
        roiMap["roiID"+string(roi.ID)] = roi.Coordinates
    }

    jsonBytes, err := json.Marshal(roiMap)
    if err != nil {
        http.Error(w, err.Error(), http.StatusInternalServerError)
        return
    }

    w.Header().Set("Content-Type", "application/json")
    w.WriteHeader(http.StatusOK)
    w.Write(jsonBytes)
}

func main() {
    appState := &AppState{
        ReceivedData: &sync.Mutex{},
        ROIs:         []ROI{},
    }

    http.HandleFunc("/receive_roi_data", func(w http.ResponseWriter, r *http.Request) {
        receiveROIData(w, r, appState)
    })

    http.HandleFunc("/get_roi_data", func(w http.ResponseWriter, r *http.Request) {
        getROIData(w, r, appState)
    })

    log.Fatal(http.ListenAndServe(":8080", nil))
}
