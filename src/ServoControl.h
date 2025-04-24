#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <Arduino.h>

class ServoControl {
public:
    ServoControl(int pin);
    void begin();
    void setAngle(int angle);
    void find();
    void stop();

private:
    int _pin;
};

#endif
