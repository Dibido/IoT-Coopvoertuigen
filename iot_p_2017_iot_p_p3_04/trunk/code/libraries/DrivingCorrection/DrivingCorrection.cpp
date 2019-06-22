// Local
#include "DrivingCorrection.h"

DrivingCorrection::DrivingCorrection(DrivingControl& control, UltrasonicSensor& lSensor, UltrasonicSensor& rSensor, uint8_t checkInterval, uint8_t margin) :
  control(control), leftDistSensor(lSensor), rightDistSensor(rSensor), checkInterval(checkInterval), correctionMargin(margin)
{
}

DrivingCorrection::~DrivingCorrection()
{
}

void DrivingCorrection::init()
{
  this->setInitDists(this->leftDistSensor.getDistance(), this->rightDistSensor.getDistance());
}

void DrivingCorrection::run()
{
  this->getDistances();

  //Left corner
  if (this->curLeftDist < (initLeftDist) && this->curRightDist > (initRightDist))
  {
    control.maneuver(STD_MOVING_SPEED_L, STD_MOVING_SPEED_R + CORRECTION_SPEED);
  }
    
  //Right corner
  else if (this->curRightDist < (initRightDist) && curLeftDist > (initLeftDist))
  {
    control.maneuver(STD_MOVING_SPEED_L - CORRECTION_SPEED, STD_MOVING_SPEED_R);
  }
  /**
  else if(this->curRightDist > (initRightDist) || this->curRightDist < (initRightDist)) {
    this->setInitDists(curLeftDist, curRightDist);
  }
  else if(this->curLeftDist > (initLeftDist) || this->curLeftDist < (initLeftDist)) {
    this->setInitDists(curLeftDist, curRightDist);
  }
  */
  else
  {
    debugln("No Correction necessary");
  }
}

void DrivingCorrection::getDistances()
{
  this->curLeftDist = this->leftDistSensor.getDistance();
  this->curRightDist = this->rightDistSensor.getDistance();
}

void DrivingCorrection::setInitDists(uint8_t leftDist, uint8_t rightDist)
{
  this->initLeftDist = leftDist;
  this->initRightDist = rightDist;
}

int8_t DrivingCorrection::getDistDifference(int8_t initDist, int8_t curDist)
{
  return initDist - curDist;
}

uint8_t DrivingCorrection::getLeftInitDist() 
{
	return this->initLeftDist;
}

uint8_t DrivingCorrection::getRightInitDist() 
{
	return this->initRightDist;
}
