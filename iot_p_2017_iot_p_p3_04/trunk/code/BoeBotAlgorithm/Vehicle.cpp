// Libraries
#include <Defines.h>
#include <Debug.h>
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
  stopped(false),
  drivingCorrection(drivingControl, leftSensor, rightSensor, 0, 0)
{
}

Vehicle::~Vehicle()
{
}

void Vehicle::vehicleSetup()
{
  pinMode(VEHICLE_LEFT_LED, OUTPUT);
  pinMode(VEHICLE_RIGHT_LED, OUTPUT);
  digitalWrite(VEHICLE_LEFT_LED, LOW);
  digitalWrite(VEHICLE_RIGHT_LED, LOW);
  leftWheel.attach(LEFT_WHEEL_PIN);
  rightWheel.attach(RIGHT_WHEEL_PIN);
  timeOfFlightSetup();
  drivingCorrection.init();
  drivingControl.maneuver(STATIONARY, STATIONARY);
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
    if (frontDistance > MAX_DIST)
    {
      drivingControl.maneuver(EXIT_MOVING_SPEED_L, EXIT_MOVING_SPEED_R);
      //Software timer for stopping the vehicle if no obstacle is detected within the time limit
      if (millis() - previousExitTime >= STOP_EXITING_TIMER)
      {
        drivingControl.maneuver(STD_MOVING_SPEED_L, STD_MOVING_SPEED_R);
        this->startExiting(false);
        this->stopDriving(true);
      }
      if (millis() - previousRightLedTime >= VEHICLE_BLINKING_TIMER)
      {
        digitalWrite(VEHICLE_RIGHT_LED, !digitalRead(VEHICLE_RIGHT_LED));
        previousRightLedTime = millis();
      }
    }
    else if (frontDistance < MAX_DIST) // Decelerating
    {
      drivingControl.maneuver(STATIONARY, STATIONARY);
      this->startExiting(false);
      this->stopDriving(true);
    }
  }
  else if (stopped)
  {
    drivingControl.changeSpeed(0);
    digitalWrite(A1, LOW);
    if (drivingControl.getLeftWheelSpeed() == STATIONARY)
    {
      stopDriving(false);
    }
  }
  else
  {
    //Do nothing
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

void Vehicle::handleMessage(const Xtea& x, const String& message, const char& messageCode)
{
  debug("Message: ");
  debugln(message);
  uint8_t encrypted[VEHICLE_MAX_MESSAGE_LENGTH];
  uint8_t decrypted[VEHICLE_MAX_MESSAGE_LENGTH];

  //Make a message to combine the messageCode and the actual message
  String tempMessage = String(uint8_t(messageCode)) + DELIMITER + message.substring(1, message.length() - 1);
  //Parse the temporary message into the encrypted array without the delimiter.
  parseMessage(tempMessage, DELIMITER, encrypted);
  //Decrypt the values from the encrypted
  x.decryptValues(VEHICLE_MAX_MESSAGE_LENGTH, encrypted, decrypted);
  debug("Decrypted message: ");
#ifdef DEBUG_MODE
  for (int i = 0; i < VEHICLE_MAX_MESSAGE_LENGTH; ++i) {
    debug(decrypted[i]);
    debug(DELIMITER);
  }
  debugln();
#endif

  switch ((char)decrypted[CHAR_POSITION]) // The childSensorId is used to indicate the message type
  {
    case VEHICLE_REGISTERED:
      if (decrypted[1] == MY_NODE_ID) {
        debugln("Registered");
      }
      break;

    case START_DRIVING:
      this->startDriving(true);
      break;

    case START_MERGING:
      this->prepareMerge(uint16_t(decrypted[1]), uint16_t(decrypted[2]));
      break;

    case HEARTBEAT:
      break;

    case EXIT_LANE:
      this->exitLane();
      break;

    case STOP_DRIVING:
      this->startDriving(false);
      this->stopDriving(true);
      break;

    default:
      debugln("Error in communication.cpp: unknown message type");
      break;
  }
}

void Vehicle::startDriving(bool drive)
{
  this->driving = drive;
}

void Vehicle::stopDriving(bool stopping)
{
  this->stopped = stopping;
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

void Vehicle::prepareMerge(const uint16_t leftDist, const uint16_t rightDist)
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
      this->startMerging(leftDist, rightDist);
    }
  }
}

void Vehicle::startMerging(const uint16_t leftDist, const uint16_t rightDist)
{
  debugln("<!--MERGING--!>");
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
  if (rightDist > MIN_EXIT_DIST && frontDistance > MAX_DIST) {
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
