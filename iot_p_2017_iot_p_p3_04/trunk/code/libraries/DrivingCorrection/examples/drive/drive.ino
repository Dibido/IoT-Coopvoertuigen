#include <DrivingCorrection.h>
#include <UltrasonicSensor.h>

Servo leftServo;
Servo rightServo;

#define ACCELERATION_SPEED 100
#define DECELERATION_SPEED 25
#define LEFT_PIN 11
#define RIGHT_PIN 12

UltrasonicSensor ls(2,3);
UltrasonicSensor rs(4,5);

DrivingControl control(leftServo, rightServo, ACCELERATION_SPEED, DECELERATION_SPEED);

DrivingCorrection dc(control, ls, rs, 20, 2);

void setup()
{
    Serial.begin(9600);
    Serial.println("Serial started!");

    leftServo.attach(LEFT_PIN);
    rightServo.attach(RIGHT_PIN);
    dc.init();
}

void loop()
{
  control.changeSpeed(200);
  dc.run();	
}
