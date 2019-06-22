// Library
#include <DrivingControl.h>

Servo leftWheel;
Servo rightWheel;

#define ACCELERATION_SPEED 100
#define DECELERATION_SPEED 25
#define LEFT_PIN 11
#define RIGHT_PIN 12

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
    dc.changeSpeed(100); // Value between -200 and 200
    delay(100);
}