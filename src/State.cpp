#include "State.h"

bool arretRecuperation = false;
bool mouvementDetecte = false;
unsigned long startTime = 0;

bool verifierGyroscope() {
    if (!arretRecuperation) {
        Vector3 GyroData = getGyroscopeData(); // Assurez-vous que getGyroscopeData() renvoie un Vector3
        // Serial.println("gyroscope : " + String(GyroData.x) + " " + String(GyroData.y) + " " + String(GyroData.z));

        if ((GyroData.x > 15.0 || GyroData.y > 15.0 || GyroData.z > 15.0) || (GyroData.x < -15.0 || GyroData.y < -15.0 || GyroData.z < -15.0)) {
            mouvementDetecte = true;
            startTime = millis();
            // Serial.println("Mouvement detecte");
        }

        if (millis() - startTime > 30000) {
            arretRecuperation = true;
            Serial.println("Arret recuperation");
        }

        return false;
    } else {
        return true;
    }
}