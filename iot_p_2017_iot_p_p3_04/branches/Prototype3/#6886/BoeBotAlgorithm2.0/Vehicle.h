#ifndef VEHICLE_H
#define VEHICLE_H

// Libraries
#include <Adafruit_VL53L0X.h>
#include <DrivingControl.h>
#include <DrivingCorrection.h>
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

// Send message types
enum sendChar
{
  REGISTER = 'R',
  SEND_DATA = 'D'
};

// Receive message types
enum receivedChar
{
  VEHICLE_REGISTERED = 'r',
  START_DRIVING = 'd',
  START_MERGING = 'm',
  HEARTBEAT = 'h',
  EXIT_LANE = 'e',
  STOP_DRIVING = 's'
};

class Vehicle
{
  public:
    Vehicle();
    ~Vehicle();

    /**
      @brief: Attaches the servo's and initialises the Time-of-Flight sensor
    */
    void vehicleSetup();
    /**
      @brief: Driving algorithm for the Boe-Bot
    */
    void drive();

    /**
      @brief: Messagehandler for messages sent by the checkpoint
      @param message: The incoming message body
      @parama messageCode: The message type that is used to determain what action must be excuted
    */
    void handleMessage(String message, char messageCode);

    void startDriving(bool drive);

    /**
      @brief: Registers the vehicle at the checkpoint
    */
    void registerVehicle();

    // Getters
    DrivingControl getDrivingControl();
    UltrasonicSensor getLeftUltrasonicSensor();
    UltrasonicSensor getRightUltrasonicSensor();
    uint8_t getFrontDistance();

    // Setters
    void setFrontDistance();

  private:
    Servo leftWheel;
    Servo rightWheel;
    DrivingControl control;
    uint8_t frontDistance;
    UltrasonicSensor left;
    UltrasonicSensor right;
    boolean driving;
    DrivingCorrection correction;
};

#endif /* VEHICLE_H */
