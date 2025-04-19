#include "getDataBME68x.h"
#include <Wire.h>

BME68xReader::BME68xReader() : bme() {}

bool BME68xReader::begin() {
    if (!bme.begin(0x76)) {
        return false;
    }
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320°C for 150 ms
    return true;
}

bool BME68xReader::readSensor() {
    if (!bme.performReading()) {
        return false;
    }
    temperature = bme.temperature;
    humidity = bme.humidity;
    pressure = bme.pressure / 100.0;
    gasResistance = bme.gas_resistance / 1000.0;
    return true;
}

std::string BME68xReader::getAllSensorData() {
    if (!readSensor()) {
        return "Erreur de lecture du BME688";
    }

    char buffer[128];
    snprintf(buffer, sizeof(buffer),
             "%.2f,%.2f,%.2f,%.2f, %.2f",
             temperature, humidity, pressure, gasResistance, millis());
    appendToLog1(buffer);
    return std::string(buffer);
}
