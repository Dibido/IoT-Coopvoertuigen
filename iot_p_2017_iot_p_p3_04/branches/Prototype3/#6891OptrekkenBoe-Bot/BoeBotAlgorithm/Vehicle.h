#ifndef VEHICLE_H
#define VEHICLE_H

// Libraries
#include <VL53L0X.h>
#include <DrivingControl.h>
#include <DrivingCorrection.h>
#include <UltrasonicSensor.h>
#include <Servo.h>
#include <Arduino.h>

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
    void handleMessage(const String& message, const char& messageCode);

    /**
        @brief Let the vehicle start draiving
    */
    void startDriving(bool drive);

    /**
        @brief: Starts merging the vehicle into the row
    */
    void startMerging(const String& message);

    /**
        @brief: Registers the vehicle at the checkpoint
    */
    void registerVehicle();

    /**
        @brief Sends the given vehicle data to the checkpoint
        @param leftSpeed Speed of the left wheel
        @param rightSpeed Speed of the right wheel
        @param frontDist Distance measured on the front of the Boe-Bot
        @param leftDist Distance measured on the left of the Boe-Bot
        @param rightDist Distance measure on the right of the Boe-Bot
    **/
    void sendData(uint8_t leftSpeed, uint8_t rightSpeed, uint8_t frontDist, uint8_t leftDist, uint8_t rightDist);

    /**
       @brief Changes the speed based on the measured front distance
    */
    void handleSpeed();

    // Getters
    DrivingControl& getDrivingControl();
    UltrasonicSensor& getLeftUltrasonicSensor();
    UltrasonicSensor& getRightUltrasonicSensor();
    uint8_t getFrontDistance();

    // Setters
    void setFrontDistance();

  private:

    /**
     * @brief Setup for the Time of Flight sensor
     */
    void timeOfFlightSetup();

    Servo leftWheel;
    Servo rightWheel;
    DrivingControl control;
    uint16_t frontDistance;
    UltrasonicSensor leftSensor;
    UltrasonicSensor rightSensor;
    VL53L0X sensor;
    bool driving;
    bool merging;
    DrivingCorrection correction;
};

#endif /* VEHICLE_H */
