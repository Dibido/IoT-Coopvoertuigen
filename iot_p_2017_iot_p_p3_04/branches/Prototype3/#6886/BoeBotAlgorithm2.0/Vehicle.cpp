// Defines
//#define DEBUG_MODE

#define REACTION_SPEED 100
#define DATA_SEND_INTERVAL 2000

//Libraries
#include <Debug.h>

// Local
#include "Vehicle.h"

// Global variables
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t measure;

Vehicle::Vehicle() :
  leftWheel(),
  rightWheel(),
  control(leftWheel, rightWheel, ACCELERATION_SPEED, DECELERATION_SPEED),
  left(L_TRIG_PIN, L_ECHO_PIN),
  right(R_TRIG_PIN, R_ECHO_PIN),
  correction(control, left, right, 0, 0)
{

}

Vehicle::~Vehicle()
{
}

void Vehicle::vehicleSetup()
{
  leftWheel.attach(LEFT_WHEEL_PIN);
  rightWheel.attach(RIGHT_WHEEL_PIN);
  lox.begin();
  correction.init();
}

void Vehicle::drive()
{
  setFrontDistance();
  if (driving)
  {
    if (frontDistance > MAX_DIST) // Accelerating
    {
      control.changeSpeed(DRIVING_SPEED);
      correction.run();
    }
    else if (frontDistance < MAX_DIST) // Decelerating
    {
      control.changeSpeed(0);
    }
  } 
  else
  {
    control.changeSpeed(0);
  }
}

DrivingControl Vehicle::getDrivingControl()
{
  return this->control;
}

UltrasonicSensor Vehicle::getLeftUltrasonicSensor()
{
  return this->left;
}

UltrasonicSensor Vehicle::getRightUltrasonicSensor()
{
  return this->right;
}

void Vehicle::handleMessage(String message, char messageCode)
{
  switch (messageCode) // The childSensorId is used to indicate the message type
  {
    case VEHICLE_REGISTERED:
            debugln(F("Vehicle registered!"));
            break;

        case START_DRIVING:
            debug(F("startDriving message received: "));
            debugln(message);
            startDriving(true);
            break;

        case START_MERGING:
            debug(F("startMerging message received: "));
            debugln(message);
            break;

        case HEARTBEAT:
            debug(F("heartbeat message received: "));
            debugln(message);
            break;

        case EXIT_LANE: 
                debug(F("exitLane message received: "));
            debugln(message);
            break;

        case STOP_DRIVING:
            debug(F("stopDriving message received: "));
            debugln(message);
            startDriving(false);
            break;

        default:
            debugln(F("Error in communication.cpp: unknown message type"));
            break;
  }
}

void Vehicle::startDriving(boolean drive)
{
  this->driving = drive;
}

uint8_t Vehicle::getFrontDistance()
{
  return this->frontDistance;
}

void Vehicle::setFrontDistance()
{
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  this->frontDistance = measure.RangeMilliMeter / 10;
}

void Vehicle::registerVehicle()
{

}

