"""
Class pacient
    id
    name
    age
    hospital_name
    doctor_name
    date_of_admission
    date_of_discharge
    meta_data: {
        device: [{
            provider: "provider",
            device_name: "device_name",
            device_type: "device_type",
            auraVersion: "auraVersion",
            currentMode: "currentMode",
            currentStatus: [{
                status: "status",
                time: "time",
                ip: "ip",
                network: "network",
                battery: "battery",
                temperature: "temperature",
                voltage: "voltage",
                current: "current",
                powerSupply: "powerSupply",
                cameraMode: "cameraMode",
            }],
        }],
        pacientStatus: [{
            ECG: "ECG",
            SpO2: "SpO2",
            BP: "BP",
            HR: "HR",
            RR: "RR",
            TEMP: "TEMP",
            GLUCOSE: "GLUCOSE",
            PULSE: "PULSE",
            BLOOD: "BLOOD",
        }],
    }
        
"""
