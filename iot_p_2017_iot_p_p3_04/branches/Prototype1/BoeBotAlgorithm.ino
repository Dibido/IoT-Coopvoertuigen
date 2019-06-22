// Local
#include "Vehicle.h"

Vehicle v;

Servo leftWheel;
Servo rightWheel;

DistanceSensor ds(A0);
DrivingControl dc(leftWheel, rightWheel, ACCELERATION_SPEED, DECELERATION_SPEED);

void setup()
{
  Serial.begin(9600);
  Serial.println("Serial started!");
  leftWheel.attach(LEFT_PIN);
  rightWheel.attach(RIGHT_PIN);

}

void loop()
{
  uint8_t frontDistance = ds.getDistance();

  if (frontDistance < MAX_DIST) {
    Serial.println("Stop");
    leftWheel.writeMicroseconds(1500);
    rightWheel.writeMicroseconds(1500);
  }
  else {
    Serial.println("Go");
    leftWheel.writeMicroseconds(1600);
    rightWheel.writeMicroseconds(1400);
  }
}
