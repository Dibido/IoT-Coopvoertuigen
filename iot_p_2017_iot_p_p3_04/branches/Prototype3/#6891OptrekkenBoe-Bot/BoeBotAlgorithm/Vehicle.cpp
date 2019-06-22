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
  correction(control, leftSensor, rightSensor, 0, 0)
{
}

Vehicle::~Vehicle()
{
}

void Vehicle::vehicleSetup()
{
  leftWheel.attach(LEFT_WHEEL_PIN);
  rightWheel.attach(RIGHT_WHEEL_PIN);

  this->timeOfFlightSetup();

  correction.init();
  driving = true;
}

void Vehicle::drive()
{
  setFrontDistance();
  if (driving)
  {
    if (frontDistance > MAX_DIST) // Accelerating
    {
      this->handleSpeed();
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

uint8_t Vehicle::getFrontDistance()
{
  return this->frontDistance;
}

void Vehicle::setFrontDistance()
{
  this->frontDistance = sensor.readRangeSingleMillimeters() / 10;
}

void Vehicle::registerVehicle()
{
}

void Vehicle::handleSpeed() {

  //If the frontDistance is between 0cm and VEHICLE_FOLLOW_DIST, the speed changes gradually based on the measured frontDistance
  if (this->frontDistance > 0 && this->frontDistance <= VEHICLE_FOLLOW_DIST)
  {
    control.changeSpeed(this->frontDistance * (VEHICLE_TOP_DRIVING_SPEED / VEHICLE_FOLLOW_DIST));
  }
  //If the frontDistance is between VEHICLE_FOLLOW_DIST and VEHICLE_MAX_FOLLOW_DIST cm, the vehicle drives at top speed
  else if (this->frontDistance > VEHICLE_FOLLOW_DIST && this->frontDistance < VEHICLE_MAX_FOLLOW_DIST)
  {
    control.changeSpeed(VEHICLE_TOP_DRIVING_SPEED);
  }
  //If the frontDistance is over VEHICLE_MAX_FOLLOW_DIST the values of the frontDistance aren't trustworthy anymore. Therefore it is implied that the vehicle is the first vehicle in the train.
  else
  {
    control.changeSpeed(DRIVING_SPEED);
  }
}

void Vehicle::timeOfFlightSetup() {
  Wire.begin();

  sensor.init();
  sensor.setTimeout(TOF_TIMEOUT);
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor.setSignalRateLimit(TOF_RATE_LIMIT);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, TOF_PULSE_PRE_RANGE);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, TOF_PULSE_FINAL_RANGE);

  sensor.setMeasurementTimingBudget(TOF_TIMING);
}

