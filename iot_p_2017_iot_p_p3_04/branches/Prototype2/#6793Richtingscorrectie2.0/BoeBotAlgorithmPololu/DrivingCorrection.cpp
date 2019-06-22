#include "DrivingCorrection.h"

uint32_t correction(DrivingControl control, UltrasonicSensor left, UltrasonicSensor right, uint32_t previousTime, DrivingState *curState) {
  //Read out distances
  int16_t leftDist = left.getDistance();
  int16_t rightDist = right.getDistance();
  //Calculate difference between distances
  int16_t distDiff = leftDist - rightDist;
  debug("Leftdist :");
  debugln(leftDist);
  debug("Rightdist :");
  debugln(rightDist);
  debug("Distance difference:");
  debugln(distDiff);
  //Print current state
  debug("State:");
  debugln(*curState);

  //Calculate correctiontime based on distance difference
  int16_t correctionTime = abs((distDiff) * 50);
  debug("correctionTime :");
  debugln(correctionTime);
  //Time to straighten the path for the measurements
  int16_t straightPathTime = 1000;

  //If the bot has moved left
  if (leftDist < rightDist)
  {
    //If we are not going right
    if (*curState != RIGHT) {
      //Turn right
      control.maneuver(0, CORRECTION_SPEED);
      *curState = RIGHT;
      debugln("Right");
    }
    //Drive right while correctiontime has not elapsed
    while (*curState == RIGHT) {
      //If correctiontime has elapsed
      if (millis() - previousTime >= correctionTime)
      {
        //Drive straight
        control.maneuver(CORRECTION_SPEED, 0);
        debugln("StraightRight");
        *curState = STRAIGHT;
        //Wait for the path to straighten out.
        delay(1000);
        previousTime = millis();
        break;
      }
    }
  }
  //If the bot has moved right
  else if (leftDist > rightDist)
  {
    //If we are not going left
    if (*curState != LEFT)
    {
      control.maneuver(CORRECTION_SPEED, 0); //Turn left
      debugln("Left");
      *curState = LEFT;
    }
    //If correctiontime has elapsed
    while (*curState == LEFT)
    {
      //If correctiontime has elapsed
      if (millis() - previousTime >= correctionTime)
      {
        //Drive straight
        control.maneuver(0, CORRECTION_SPEED);
        debugln("StraightLeft");
        *curState = STRAIGHT;
        //Wait for the path to straighten out.
        delay(1000);
        previousTime = millis();
        break;
      }
    }
  }
  //Bot is on correct path
  else
  {
    *curState = STRAIGHT;
  }
  return previousTime;
}
