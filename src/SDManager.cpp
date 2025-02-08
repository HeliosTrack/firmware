#include "SDManager.h"

SDManager::SDManager(uint8_t csPin) : _csPin(csPin) {}


bool SDManager::appendToFile(const char *filename, const String &data) {
    if (!SD.begin(_csPin)) {
        Serial.println("Erreur : Impossible d'initialiser la carte SD !");
        return false;
    }

    // Ouvre en mode append, s'il n'existe pas, crée le fichier
    File file = SD.open(filename, FILE_APPEND);
    if (!file) {
        Serial.printf("Erreur : Impossible d'ouvrir ou de créer %s !\n", filename);
        return false;
    }

    file.println(data);  // Ajoute une nouvelle ligne au fichier
    file.close();
    Serial.printf("Données ajoutées à %s : %s\n", filename, data.c_str());
    return true;
}
