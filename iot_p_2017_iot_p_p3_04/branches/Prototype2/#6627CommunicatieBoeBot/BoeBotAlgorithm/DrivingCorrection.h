#ifndef DRIVINGCORRECTION_H_
#define DRIVINGCORRECTION_H_

#include <stdint.h>
#include <DrivingControl.h>
#include <IRSensor.h>
#include <UltrasonicSensor.h>

#include <Arduino.h>

#define CORRECTION_SPEED  40
#define DRIVING_SPEED 100

void correction(DrivingControl control, UltrasonicSensor left, UltrasonicSensor right);

#endif /*DRIVINGCORRECTION_H_*/
