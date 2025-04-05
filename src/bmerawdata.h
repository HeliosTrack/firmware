#ifndef BMERAWDATA_H
#define BMERAWDATA_H

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "bsec2.h"
#include "SDLogger.h"

#ifndef SDCARD_CS
#define SDCARD_CS 47  // Broche CS de la carte SD (modifiable selon ton matériel)
#endif

#define BME68X_I2C_ADDR 0x76
#define SDA_CUSTOM 3  // Nouvelle broche SDA
#define SCL_CUSTOM 2  // Nouvelle broche SCL

class BMERawData {
    public:
        BMERawData();
        bool begin();
        void logData();

    private:
        static BMERawData* instancePtr;
        File dataFile;  // ✅ Ajout de la variable membre pour stocker le fichier SD
        String filename;

        static void newDataCallback(const bme68xData data, const bsecOutputs outputs, Bsec2 bsec);
};

#endif
