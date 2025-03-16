#include "State.h"

unsigned long startTime = 0;
bool mouvementDetecte = false;
bool arretRecuperation = false;

bool verifierGyroscope() {
    
    Vector3 GyroData = getGyroscopeData(); // Assurez-vous que getGyroscopeData() renvoie un Vector3
    Serial.println("gyroscope : " + String(GyroData.x) + " " + String(GyroData.y) + " " + String(GyroData.z));

    
    return true;
}
