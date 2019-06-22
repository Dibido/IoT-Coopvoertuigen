#include <Arduino.h>
#include "initBot.h"
#include "moveBot.h"

void maneuver(int speedLeft, int speedRight) {
  // speedLeft, speedRight ranges: Backward  Linear  Stop  Linear   Forward
  //                               -200      -100......0......100       200
  servoLeft.writeMicroseconds(1500 + speedLeft);   // Set Left servo speed
  servoRight.writeMicroseconds(1500 - speedRight); // Set right servo speed
}

void maneuver(int speedLeft, int speedRight, int msTime) {
  // speedLeft, speedRight ranges: Backward  Linear  Stop  Linear   Forward
  //                               -200      -100......0......100       200
  servoLeft.writeMicroseconds(1500 + speedLeft);   // Set Left servo speed
  servoRight.writeMicroseconds(1500 - speedRight); // Set right servo speed
  if (msTime == -1)                                // if msTime = -1
  {
    servoLeft.detach();                            // Stop servo signals
    servoRight.detach();
  }
  delay(msTime);                                   // Delay for msTime
}

void stopManeuver() {
  maneuver(0, 0);
}

void goForward(int speed) {
  maneuver(speed, speed);
}

void goBackwards(int speed) {
  maneuver(-speed, -speed);
}

void turnOnPlace(long degrees) {
  Serial.println("NOT a normal car turn!!");
  degrees *= 1000;
  bool done = false;
  while (!done) {
    if (degrees < 0) {
      degrees++;
      if (degrees == 0) {
        done = true;
        Serial.println("Done");
        break;
      }
      maneuver(-200, 200);
    } else if (degrees > 0) {
      degrees--;
      if (degrees == 0) {
        done = true;
        Serial.println("Done");
        break;
      }
      maneuver(200, -200);
    } else {
      maneuver(0, 0);
      done = true;
    }
  }

  stopManeuver();
}

void carTurn(long degrees) {
//  degrees *= 5000;
//  Serial.println("Change it to use something like a compas module");
//  bool done = false;
//  while (!done) {
//    if (degrees < 0) {
//      degrees++;
//      if (degrees == 0) {
//        done = true;
//        Serial.println("Done");
//        break;
//      }
//      maneuver(50, 200);
//    } else if (degrees > 0) {
//      degrees--;
//      if (degrees == 0) {
//        done = true;
//        Serial.println("Done");
//        break;
//      }
//      maneuver(200, 50);
//    } else {
//      maneuver(0, 0);
//      done = true;
//    }
//  }
//
//  stopManeuver();
}

