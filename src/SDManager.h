#ifndef SDMANAGER_H
#define SDMANAGER_H

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

class SDManager {
public:
    SDManager(uint8_t csPin);
    bool appendToFile(const char *filename, const String &data); // Ajoute une ligne et crée le fichier si nécessaire

private:
    uint8_t _csPin;
};

#endif // SDMANAGER_H
