//Libraries
#include <Debug.h>
#include <Defines.h>
#include <Wire.h>

// Local
#include "Vehicle.h"

Vehicle::Vehicle() :
  leftWheel(),
  rightWheel(),
  control(leftWheel, rightWheel, ACCELERATION_SPEED, DECELERATION_SPEED),
  leftSensor(L_TRIG_PIN, L_ECHO_PIN),
  rightSensor(R_TRIG_PIN, R_ECHO_PIN),
  correction(control, leftSensor, rightSensor, 0, 0),
  merging(false)
{
}

Vehicle::~Vehicle()
{
}

void Vehicle::vehicleSetup() 
{
  leftWheel.attach(LEFT_WHEEL_PIN);
  rightWheel.attach(RIGHT_WHEEL_PIN);
  Wire.begin();
  tofSensor.init();
  tofSensor.setTimeout(TOF_TIMEOUT);
  // lower the return signal rate limit (default is 0.25 MCPS)
  tofSensor.setSignalRateLimit(TOF_RATE_LIMIT);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  tofSensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, TOF_PULSE_PRE_RANGE);
  tofSensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, TOF_PULSE_FINAL_RANGE);

  tofSensor.setMeasurementTimingBudget(TOF_TIMING);
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

DrivingControl& Vehicle::getDrivingControl()
{
  return this->control;
}

UltrasonicSensor& Vehicle::getLeftUltrasonicSensor()
{
  return this->leftSensor;
}

UltrasonicSensor& Vehicle::getRightUltrasonicSensor()
{
  return this->rightSensor;
}

void Vehicle::handleMessage(const String& message, const char& messageCode)
{
  switch (messageCode) // The childSensorId is used to indicate the message type
  {
    case VEHICLE_REGISTERED:
      break;

    case START_DRIVING:
      this->startDriving(true);
      break;

    case START_MERGING:
      this->startMerging(message);
      break;

    case HEARTBEAT:
      break;

    case EXIT_LANE:
      break;

    case STOP_DRIVING:
      this->startDriving(false);
      break;

    default:
      debugln(F("Error in communication.cpp: unknown message type"));
      break;
  }
}

void Vehicle::startDriving(bool drive)
{
  this->driving = drive;
}

void Vehicle::startMerging(const String& message)
{
  this->merging = false;
  //Boolean to check whether the first car has passed
  bool carPassed = false;
  bool startedTimer = false;
  uint32_t gapStartTime;

  //Check for the first vehicle
  //Read standard distance
  uint16_t defaultDist = this->leftSensor.getDistance();
  
  //While loop to check for room to merge
  while (!this->merging)
  {
    //No car has passed
    while (!carPassed)
    {
      //Vehicle is to the side
      if (checkVehicleDifference(defaultDist))
      {
        //Wait for vehicle to pass
        while (checkVehicleDifference(defaultDist))
        {
        }
        //First car has passed
        carPassed = true;
      }
    }
    
    //Distance is back to default within margin
    uint16_t curDist = this->leftSensor.getDistance();
    if (!startedTimer && (curDist >= defaultDist - MERGING_STANDARD_MEASUREMENT_MARGIN && curDist <= defaultDist + MERGING_STANDARD_MEASUREMENT_MARGIN))
    {
      //Start timer
      startedTimer = true;
      gapStartTime = millis();
    }
    //Found new vehicle
    if (startedTimer && checkVehicleDifference(defaultDist))
    {
      //Wait for vehicle to pass
      while (checkVehicleDifference(defaultDist))
      {
      }
      //Reset timer
      startedTimer = false;
    }
    
    //Time is longer than margin
    else if (startedTimer && millis() - gapStartTime >= MERGING_GAPTIME_MARGIN)
    {
      //Start merging
      this->merging = true;
      this->merge(message);
    }
  }
}

bool Vehicle::checkVehicleDifference(const uint16_t defaultDist)
{
  //Calculate difference with new distance
  uint16_t curDist = this->leftSensor.getDistance();
  uint8_t absDistDiff = abs(int8_t(defaultDist - curDist));
  return (absDistDiff >= MERGING_CARWIDTH);
}

void Vehicle::merge(const String& message)
{
  //Read out new path
  //Message example /15;5/
  //Read from past '/' to the first ';'
  //  uint16_t leftDist = uint16_t(message.substring(message.indexOf(START) + 1, message.indexOf(DELIMITER)).toInt());
  //Read from first ';' to the end minus one
  //  uint16_t rightDist = uint16_t(message.substring(message.indexOf(DELIMITER), message.length() - 1).toInt());
  //Enable turn signal
  //debugln("!--Merging--!");
}

uint8_t Vehicle::getFrontDistance()
{
  return this->frontDistance;
}

void Vehicle::setFrontDistance()
{
  //  this->frontDistance = tofSensor.readRangeSingleMillimeters() / 10;
}

void Vehicle::registerVehicle()
{
}
