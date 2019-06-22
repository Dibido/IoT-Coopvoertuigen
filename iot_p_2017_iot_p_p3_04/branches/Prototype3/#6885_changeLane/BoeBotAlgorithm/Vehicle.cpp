// Libraries
#include <Debug.h>
#include <Defines.h>
#include <Wire.h>

// Local
#include "Vehicle.h"

Vehicle::Vehicle() :
  leftWheel(),
  rightWheel(),
  drivingControl(leftWheel, rightWheel, ACCELERATION_SPEED, DECELERATION_SPEED),
  leftSensor(L_TRIG_PIN, L_ECHO_PIN),
  rightSensor(R_TRIG_PIN, R_ECHO_PIN),
  drivingCorrection(drivingControl, leftSensor, rightSensor, 0, 0),
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
  drivingCorrection.init();
}

void Vehicle::drive()
{
  setFrontDistance();

  if (driving)
  {
    if (frontDistance > MAX_DIST) // Accelerating
    {
      drivingControl.changeSpeed(DRIVING_SPEED);
      drivingCorrection.run();
    }
    else if (frontDistance < MAX_DIST) // Decelerating
    {
      drivingControl.changeSpeed(0);
    }
  }
  else
  {
    drivingControl.changeSpeed(0);
  }
}

DrivingControl& Vehicle::getDrivingControl()
{
  return this->drivingControl;
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
      this->prepareMerge(message);
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

bool Vehicle::checkVehicleDifference(const uint16_t defaultDist)
{
  // Calculate difference with new distance
  uint16_t sum = 0;
  for (size_t i = 0; i < MERGING_DIFF_COUNT; i++)
  {
    sum += this->leftSensor.getDistance();
  }
  uint16_t avg = sum / MERGING_DIFF_COUNT;
  int8_t distDiff = avg - defaultDist;
  uint8_t absDistDiff = abs(distDiff);
  return (absDistDiff >= MERGING_CARWIDTH);
}

void Vehicle::prepareMerge(const String& message)
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
    while (carPassed == false)
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
        startedTimer = true;
        gapStartTime = millis();
      }
    }
    if (startedTimer && checkVehicleDifference(defaultDist)) //Found new vehicle
    {
      //Wait for vehicle to pass
      while (checkVehicleDifference(defaultDist))
      {
      }
      //Reset timer
      startedTimer = true;
      gapStartTime = millis();
    }

    else if (startedTimer && millis() - gapStartTime >= MERGING_GAPTIME_MARGIN) //Time is longer than margin
    {
      //Start merging
      this->merging = true;

      Serial.println("CALLING START MERGING"); // TODO
      this->startMerging(message);
    }
  }
}

void Vehicle::startMerging(const String& message)
{
  // Read out new path
  // Message example /15;5/
  uint16_t leftDist = uint16_t(message.substring(message.indexOf(START) + 1, message.indexOf(DELIMITER)).toInt());
  // Read from the first ';' to the end minus one char
  uint16_t rightDist = uint16_t(message.substring(message.indexOf(DELIMITER) + 1, message.length() - 1).toInt());

  Serial.println("New init dist ge-set!"); // TODO
  Serial.print("left: "); // TODO
  Serial.println(leftDist); // TODO
  Serial.print(", right: "); // TODO
  Serial.println(rightDist); // TODO

  drivingCorrection.setInitDists(leftDist, rightDist);
  this->startDriving(true);
}

uint8_t Vehicle::getFrontDistance()
{
  return this->frontDistance;
}

void Vehicle::setFrontDistance()
{
  this->frontDistance = tofSensor.readRangeSingleMillimeters() / 10;
}
