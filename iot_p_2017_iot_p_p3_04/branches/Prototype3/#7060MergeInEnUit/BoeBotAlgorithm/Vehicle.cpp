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
  driving(false),
  merging(false),
  exiting(false),
  drivingCorrection(drivingControl, leftSensor, rightSensor, 0, 0)
{
}

Vehicle::~Vehicle()
{
}

void Vehicle::vehicleSetup()
{
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  leftWheel.attach(LEFT_WHEEL_PIN);
  rightWheel.attach(RIGHT_WHEEL_PIN);

  timeOfFlightSetup();

  drivingCorrection.init();
  //64;22
  this->prepareMerge("/55;37/");
}

void Vehicle::timeOfFlightSetup() {
  Wire.begin();

  tofSensor.init();
  tofSensor.setTimeout(TOF_TIMEOUT);
  // lower the return signal rate limit (default is 0.25 MCPS)
  tofSensor.setSignalRateLimit(TOF_RATE_LIMIT);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  tofSensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, TOF_PULSE_PRE_RANGE);
  tofSensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, TOF_PULSE_FINAL_RANGE);

  tofSensor.setMeasurementTimingBudget(TOF_TIMING);
}

void Vehicle::drive()
{
  setFrontDistance();
  //If driving
  debug("curLdist : ");
  debug(this->leftSensor.getDistance());
  debug("\t curRdist : ");
  debugln(this->rightSensor.getDistance());
  //If merging
  if (merging)
  {
    drivingControl.changeSpeed(VEHICLE_TOP_DRIVING_SPEED);
    drivingCorrection.run();
    if (frontDistance < MAX_DIST) // Decelerating
    {
      this->merging = false;
    }
  }
  else if (driving)
  {
    if (frontDistance > MAX_DIST) // Accelerating
    {
      this->handleSpeed();
      drivingCorrection.run();
    }
    else if (frontDistance < MAX_DIST) // Decelerating
    {
      drivingControl.changeSpeed(0);
    }
  }

  //If exiting
  else if (exiting)
  {
    drivingControl.maneuver(EXIT_MOVING_SPEED_L, EXIT_MOVING_SPEED_R);
    if (frontDistance > MAX_DIST) // Accelerating
    {
      //Software timer for stopping the vehicle if no obstacle is detected within the time limit
      if (millis() - previousExitTime >= STOP_EXITING_TIMER)
      {
        drivingControl.maneuver(STD_MOVING_SPEED_L, STD_MOVING_SPEED_R);
        this->startExiting(false);
        digitalWrite(A1, LOW);
      }
      if (millis() - previousRightLedTime >= 500)
      {
        digitalWrite(A1, !digitalRead(A1));
        previousRightLedTime = millis();
      }
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
      this->exitLane();
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

void Vehicle::startExiting(bool exitBool)
{
  this->exiting = exitBool;
}

bool Vehicle::checkVehicleDifference(const uint16_t defaultDist)
{
  //Check for x consecutive changes
  uint8_t changeCount = 0;
  while (changeCount < MERGING_CHANGE_COUNT)
  {
    // Calculate difference with new distance
    uint16_t sum = 0;
    for (size_t i = 0; i < MERGING_DIFF_COUNT; i++)
    {
      sum += this->leftSensor.getDistance();
    }
    uint16_t avg = sum / MERGING_DIFF_COUNT;
    int16_t distDiff = avg - defaultDist;
    uint16_t absDistDiff = abs(distDiff);
    debug("def : ");
    debug(defaultDist);
    debug("avg : ");
    debug(avg);
    debug("\t diff : ");
    debugln(absDistDiff);
    
    //Vehicle to the side
    if (absDistDiff >= MERGING_CARWIDTH)
    {
      changeCount++;
    }
    else //No vehicle
    {
      return false;
    }
  }
  return true;
}

void Vehicle::prepareMerge(const String & message)
{
  debugln("Started merging");
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
        debugln("Detected vehicle");
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
      this->startMerging(message);
    }
  }
}

void Vehicle::startMerging(const String & message)
{
  debugln("<!--MERGING--!>");
  // Read out new path
  // Message example /15;5/
  uint16_t leftDist = uint16_t(message.substring(message.indexOf(START) + 1, message.indexOf(DELIMITER)).toInt());
  // Read from the first ';' to the end minus one char
  uint16_t rightDist = uint16_t(message.substring(message.indexOf(DELIMITER) + 1, message.length() - 1).toInt());
  //Setting new path
  debug("New path : ");
  debug("\t left : ");
  debug(leftDist);
  debug("\t right : ");
  debugln(rightDist);
  drivingCorrection.setInitDists(leftDist, rightDist);
  this->startDriving(true);
}

void Vehicle::handleSpeed() {

  //If the frontDistance is between 0cm and VEHICLE_FOLLOW_DIST, the speed changes gradually based on the measured frontDistance
  if (this->frontDistance > 0 && this->frontDistance <= VEHICLE_FOLLOW_DIST)
  {
    drivingControl.changeSpeed(this->frontDistance * (VEHICLE_TOP_DRIVING_SPEED / VEHICLE_FOLLOW_DIST));
  }
  //If the frontDistance is between VEHICLE_FOLLOW_DIST and VEHICLE_MAX_FOLLOW_DIST cm, the vehicle drives at top speed
  else if (this->frontDistance > VEHICLE_FOLLOW_DIST && this->frontDistance < VEHICLE_MAX_FOLLOW_DIST)
  {
    drivingControl.changeSpeed(VEHICLE_TOP_DRIVING_SPEED);
  }
  //If the frontDistance is over VEHICLE_MAX_FOLLOW_DIST the values of the frontDistance aren't trustworthy anymore. Therefore it is implied that the vehicle is the first vehicle in the train.
  else
  {
    drivingControl.changeSpeed(DRIVING_SPEED);
  }
}

void Vehicle::exitLane() {
  uint8_t rightDist = this->rightSensor.getDistance();
  if (rightDist > MIN_EXIT_DIST) {
    this->startExiting(true);
    this->startDriving(false);

    previousExitTime = millis();
    previousRightLedTime = millis();
  }
}


uint8_t Vehicle::getFrontDistance()
{
  return this->frontDistance;
}

void Vehicle::setFrontDistance()
{
  this->frontDistance = tofSensor.readRangeSingleMillimeters() / 10;
}
