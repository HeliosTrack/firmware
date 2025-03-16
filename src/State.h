#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
#include "motion/QMI8658/qmi.h"

extern bool arretRecuperation;
extern bool mouvementDetecte;
extern unsigned long startTime;

bool verifierGyroscope();

#endif // STATE_H