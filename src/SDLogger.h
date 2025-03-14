#ifndef SDLOGGER_H
#define SDLOGGER_H

#include <SD.h>
#include <SPI.h>

#define SDCARD_CS 47  // Broche CS de la carte SD (modifiable selon ton matériel)

// Prototype pour enregistrer des données CSV
void appendToLog(float param1, float param2, int param3);
void initSDCard();

#endif  // SDLOGGER_H
