#ifndef GETDATABME68X_H
#define GETDATABME68X_H

#include <Adafruit_BME680.h>
#include <string>
#include "SDLogger.h"

class BME68xReader {
public:
    BME68xReader();
    bool begin();
    std::string getAllSensorData();

private:
    Adafruit_BME680 bme;
    float temperature;
    float humidity;
    float pressure;
    float gasResistance;

    bool readSensor();
};

#endif // GETDATABME68X_H
