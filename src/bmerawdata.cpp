#include "bmerawdata.h"
#include "SDLogger.h"
#include <ArduinoJson.h>
#include <bsec2.h>
#include <SD.h>

#define SAMPLE_RATE BSEC_SAMPLE_RATE_ULP

Bsec2 envSensor;
BMERawData* BMERawData::instancePtr = nullptr;

BMERawData::BMERawData() {}

bool BMERawData::begin() {
    instancePtr = this;  // Stocker l'instance;
    Wire.begin(SDA_CUSTOM, SCL_CUSTOM);  // Initialiser le bus I2C avec les broches personnalisées


    Serial.println("Scanning I2C...");
    for (byte addr = 1; addr < 127; addr++) {
        Wire.beginTransmission(addr);
        if (Wire.endTransmission() == 0) {
            Serial.print("Found device at 0x");
            Serial.println(addr, HEX);
        }
    }


    if (!envSensor.begin(BME68X_I2C_ADDR, Wire)) {
        Serial.println("❌ Erreur : Impossible d'initialiser le BME688 !");
    } else {
        Serial.println("✅ BME688 détecté !");
    }

    // 🟢 Souscription aux capteurs BSEC
    bsecSensor sensorList[] = {
        BSEC_OUTPUT_IAQ,
        BSEC_OUTPUT_RAW_TEMPERATURE,
        BSEC_OUTPUT_RAW_PRESSURE,
        BSEC_OUTPUT_RAW_HUMIDITY,
        BSEC_OUTPUT_RAW_GAS,
        BSEC_OUTPUT_CO2_EQUIVALENT,
        BSEC_OUTPUT_BREATH_VOC_EQUIVALENT
    };

    if (!envSensor.updateSubscription(sensorList, ARRAY_LEN(sensorList), SAMPLE_RATE)) {
        Serial.println("❌ Erreur : Impossible de souscrire aux capteurs BSEC !");
        return true;
    }

    envSensor.attachCallback(BMERawData::newDataCallback);
    return true;
}

void BMERawData::logData() {
    if (!envSensor.run()) {
        Serial.println("⚠️ Attention : Pas de nouvelles données !");
        return;
    }

    
}

// 🟢 Callback pour enregistrer les données
void BMERawData::newDataCallback(const bme68xData data, const bsecOutputs outputs, Bsec2 bsec) {
    if (!outputs.nOutputs || !instancePtr) return;

    float iaq = NAN, temperature = NAN, pressure = NAN, humidity = NAN;
    float gas_resistance = NAN, co2_equivalent = NAN, breath_voc = NAN;

    for (uint8_t i = 0; i < outputs.nOutputs; i++) {
        const bsecData output = outputs.output[i];
        switch (output.sensor_id) {
            case BSEC_OUTPUT_IAQ:
                iaq = output.signal;
                break;
            case BSEC_OUTPUT_RAW_TEMPERATURE:
                temperature = output.signal;
                break;
            case BSEC_OUTPUT_RAW_PRESSURE:
                pressure = output.signal;
                break;
            case BSEC_OUTPUT_RAW_HUMIDITY:
                humidity = output.signal;
                break;
            case BSEC_OUTPUT_RAW_GAS:
                gas_resistance = output.signal;
                break;
            case BSEC_OUTPUT_CO2_EQUIVALENT:
                co2_equivalent = output.signal;
                break;
            case BSEC_OUTPUT_BREATH_VOC_EQUIVALENT:
                breath_voc = output.signal;
                break;
            default:
                break;
        }
    }

    Serial.println(iaq);
    Serial.println(temperature);
    Serial.println(pressure);
    Serial.println(humidity);
    Serial.println(gas_resistance);
    Serial.println(co2_equivalent);
    Serial.println(breath_voc);
    Serial.println("--------------------");
}
