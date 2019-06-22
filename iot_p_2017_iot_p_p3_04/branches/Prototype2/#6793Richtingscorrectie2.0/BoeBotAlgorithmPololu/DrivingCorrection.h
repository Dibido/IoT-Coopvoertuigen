#ifndef DRIVINGCORRECTION_H_
#define DRIVINGCORRECTION_H_

#include <stdint.h>
#include <DrivingControl.h>
#include <IRSensor.h>
#include <UltrasonicSensor.h>
#include <Debug.h>

#include <Arduino.h>

#include "Vehicle.h"

#define CORRECTION_SPEED 40
#define DRIVING_SPEED 100

uint32_t correction(DrivingControl control, UltrasonicSensor left, UltrasonicSensor right, uint32_t previousTime, DrivingState *curState);

#endif /*DRIVINGCORRECTION_H_*/
