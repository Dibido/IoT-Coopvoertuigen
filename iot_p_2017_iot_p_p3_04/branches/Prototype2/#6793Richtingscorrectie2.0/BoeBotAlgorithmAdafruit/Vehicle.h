#ifndef VEHICLE_H
#define VEHICLE_H

// Libraries
#include <Adafruit_VL53L0X.h>

#include <DrivingControl.h>
#include <IRSensor.h>
#include <UltrasonicSensor.h>
#include <Servo.h>
#include <Arduino.h>

#define ACCELERATION_SPEED 5
#define DECELERATION_SPEED 10
#define DRIVING_SPEED 100

#define MAX_DIST 16

#define SENSOR_PIN A0

#define LEFT_WHEEL_PIN 11
#define RIGHT_WHEEL_PIN 12

#define L_ECHO_PIN 5
#define R_ECHO_PIN 3

#define L_TRIG_PIN 4
#define R_TRIG_PIN 2

typedef enum {
  STRAIGHT,
  LEFT,
  RIGHT
} State;

class Vehicle
{
  public:
    Vehicle();
    ~Vehicle();

    void vehicleSetup();
    void drive();

  private:
    Servo leftWheel;
    Servo rightWheel;
    DrivingControl control;
    IRSensor ir;
    UltrasonicSensor left;
    UltrasonicSensor right;
    uint32_t previousTime;
    State curState;
};

#endif /* VEHICLE_H */
