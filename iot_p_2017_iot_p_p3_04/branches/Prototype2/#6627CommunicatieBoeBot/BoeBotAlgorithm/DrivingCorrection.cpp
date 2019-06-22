#include "DrivingCorrection.h"

void correction(DrivingControl control, UltrasonicSensor left, UltrasonicSensor right) {
  int16_t leftDist = left.getDistance();
  int16_t rightDist = right.getDistance();

  if (leftDist < rightDist)
  {
    control.maneuver(0, CORRECTION_SPEED);
    Serial.println("Right");
  } else if (rightDist < leftDist)
  {
    control.maneuver(CORRECTION_SPEED, 0);
    Serial.println("Left");
  }
}
