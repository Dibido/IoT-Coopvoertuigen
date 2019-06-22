#ifndef MOVEBOT_H
#define MOVEBOT_H

void maneuver(int speedLeft, int speedRight);
void maneuver(int speedLeft, int speedRight, int msTime);

void stopManeuver();

void goForward(int speed);
void goBackwards(int speed);
void turnOnPlace(long degrees);
void carTurn(long degrees);

#endif
