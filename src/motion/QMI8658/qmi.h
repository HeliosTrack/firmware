#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#pragma once

struct Vector3 {
    float x, y, z;
};


void RunOnceQMI();
Vector3 getAccelerometerData();
Vector3 getGyroscopeData();