#include <Arduino.h>
#include "initBot.h"

Servo servoLeft;
Servo servoRight;

void setupBot() {
  servoLeft.attach(11);
  servoRight.attach(12);
}

