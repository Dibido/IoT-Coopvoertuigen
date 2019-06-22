#include "DrivingCorrection.h"

uint32_t correction(DrivingControl control, UltrasonicSensor left, UltrasonicSensor right, uint32_t previousTime, State *curState) {
  int16_t leftDist = left.getDistance();
  int16_t rightDist = right.getDistance();

  Serial.print("Hallow? ");
  Serial.println(*curState);
  
  if (leftDist < rightDist)
  {
    if (*curState != RIGHT) {
      control.maneuver(0, CORRECTION_SPEED); //Turn right
      Serial.println("Right");
    }
    
    if (millis() - previousTime >= 3000) {
      previousTime = millis();
      control.maneuver(0, 0); //Drive straight
      Serial.println("StraightRight");
    }
    *curState = RIGHT;

  } else if (rightDist < leftDist)
  {
    if (*curState != LEFT) {
      control.maneuver(CORRECTION_SPEED, 0); //Turn left
      Serial.println("Left");
    }

    if (millis() - previousTime >= 3000) {
      previousTime = millis();
      control.maneuver(0, 0); //Drive straight
      Serial.println("StraightLeft");
    }
    *curState = LEFT;
  }
  else {
    *curState = STRAIGHT;
  }
  return previousTime;
}
