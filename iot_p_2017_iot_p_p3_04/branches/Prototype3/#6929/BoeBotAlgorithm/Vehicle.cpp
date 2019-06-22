// Defines
#define DEBUG_MODE


// Local
#include "Vehicle.h"
#include <DrivingCorrection.h>

//Libraries
#include <Debug.h>


Adafruit_VL53L0X lox = Adafruit_VL53L0X();

VL53L0X_RangingMeasurementData_t measure;

Vehicle::Vehicle() :
  leftWheel(),
  rightWheel(),
  control(leftWheel, rightWheel, ACCELERATION_SPEED, DECELERATION_SPEED),
  ir(SENSOR_PIN),
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
  //uint8_t frontDistance = ir.getDistance();

  lox.rangingTest(&measure, true); // pass in 'true' to get debug data printout!

  uint8_t frontDistance = measure.RangeMilliMeter / 10;

  //uint8_t frontDistance = 25;

  debug("Front distance\t\t");
  debugln(frontDistance);

  if (frontDistance > MAX_DIST) // Accelerating
  {
    control.changeSpeed(DRIVING_SPEED);
//    correction(control, left, right);
    correction.run();
    debugln("Correcting");

    if (control.getLeftWheelSpeed() < STATIONARY + DRIVING_SPEED) // If desired speed is not reached yet
    {
      //      debug("+ Speeding up..\t\t(");
      //      debug(control.getLeftWheelSpeed());
      //      debug(" > ");
      //      debug(STATIONARY + DRIVING_SPEED);
      //      debugln(")");
    }
  }
  else if (frontDistance < MAX_DIST) // Decelerating
  {
    control.changeSpeed(0);
    debugln("Stahp");
    if (control.getLeftWheelSpeed() > STATIONARY) // If desired speed is not reached yet
    {
      debug("- Slowing down..\t(");
      debug(control.getLeftWheelSpeed());
      debug(" > ");
      debug(STATIONARY);
      debugln(")");
    }
  }
  else{
     debugln("Els!");
  }
}
