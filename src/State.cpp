#include "State.h"

bool arretRecuperation = false;
bool mouvementDetecte = false;
unsigned long startTime = 0;

bool verifierGyroscope() {
    if (!arretRecuperation) {
        Vector3 GyroData = getGyroscopeData();
        // Serial.println("gyroscope : " + String(GyroData.x) + " " + String(GyroData.y) + " " + String(GyroData.z));

        bool mouvement = (GyroData.x > 15.0 || GyroData.y > 15.0 || GyroData.z > 15.0) ||
                         (GyroData.x < -15.0 || GyroData.y < -15.0 || GyroData.z < -15.0);
        
        // Serial.println(millis() - startTime);

        if (mouvement && !mouvementDetecte) {
            mouvementDetecte = true;
            startTime = millis();
            Serial.println("Détection de mouvement - démarrage du chrono");
        }

        if (mouvementDetecte && millis() - startTime > 90000) {
            arretRecuperation = true;
            Serial.println("Arret recuperation après 30 secondes");
        }

        return false;
    } else {
        return true;
    }
}
