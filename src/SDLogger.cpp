#include "SDLogger.h"


void initSDCard() {
    if (!SD.begin(SDCARD_CS)) {  
        Serial.println("⚠️ Échec du montage de la carte SD !");
        return;
    }
    Serial.println("✅ Carte SD détectée et montée avec succès.");

    if (!SD.exists("/log.csv")) {
        File logFile = SD.open("/log.csv", FILE_WRITE);
        if (logFile) {
            logFile.println("Timestamp,Param1,Param2,Param3");
            logFile.close();
            Serial.println("✅ Fichier log.csv créé avec succès !");
        } else {
            Serial.println("❌ Échec de la création du fichier log.csv !");
        }
    }

    if (!SD.exists("/BME.csv")) {
        File logFile = SD.open("/BME.csv", FILE_WRITE);
        if (logFile) {
            logFile.println("Timestamp,Param1,Param2,Param3");
            logFile.close();
            Serial.println("✅ Fichier log.csv créé avec succès !");
        } else {
            Serial.println("❌ Échec de la création du fichier log.csv !");
        }
    }
}

void appendToLog1(std::string data) {
    File logFile = SD.open("/BME.csv", FILE_APPEND);
    if (logFile) {
        logFile.println(data.c_str());
        logFile.close();
    } else {
        Serial.println("❌ Impossible d'écrire dans BME.csv !");
    }
}

void appendToLog(float param1, float param2) {
    File logFile = SD.open("/log.csv", FILE_APPEND);
    if (logFile) {
        unsigned long timestamp = millis();
        logFile.print(timestamp);
        logFile.print(",");
        logFile.print(param1);
        logFile.print(",");
        logFile.print(param2);
        logFile.println("");
        logFile.close();
        Serial.println("📝 Données ajoutées !");
    } else {
        Serial.println("❌ Impossible d'écrire dans log.csv !");
    }
}
