#include "ServoControl.h"
#include <ESP32Servo.h>

static Servo myServo;

ServoControl::ServoControl(int pin) : _pin(pin) {}

void ServoControl::begin() {
    myServo.setPeriodHertz(50); // Standard 50 Hz for SG90
    myServo.attach(_pin, 500, 2400); // Pulse width between 0° and 180°
}

void ServoControl::setAngle(int angle) {
    myServo.write(angle);
}

void ServoControl::find() {
    for (int angle = 70; angle <= 110; angle++) {
        myServo.write(angle);
        Serial.println(angle);
        delay(500);
    }
}

void ServoControl::stop() {
    myServo.detach();
}