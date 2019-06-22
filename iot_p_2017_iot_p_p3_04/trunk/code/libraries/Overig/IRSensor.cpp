#include "IRSensor.h"

IRSensor::IRSensor(uint8_t sensorPin) : sensorPin(sensorPin), sensorState(SENSORSTATE::ON), offDuration(0)
{
  pinMode(sensorPin, INPUT);
}

IRSensor::~IRSensor()
{

}

int16_t IRSensor::getDistance()
{
  uint16_t dist = analogRead(this->sensorPin);

  if (this->sensorState == SENSORSTATE::ON)
  {
        if(isValid(dist) == BETWEEN)
        {
            return 4800 / (dist - 20);
        }
        else
        {
            return isValid(dist);
        }
    }
    else
    {
        //If the duration is set
        if (offDuration > 0)
        {
          //If the duration has elapsed
          if (millis() - this->offTime >= this->offDuration)
          {
            this->sensorState = SENSORSTATE::ON;
            this->offDuration = 0;
            return dist;
            }
        }
    }
    return 0;
}

bool IRSensor::isEnabled()
{
  return this->sensorState == SENSORSTATE::ON;
}

void IRSensor::turnOff()
{
  this->sensorState = SENSORSTATE::OFF;
}

void IRSensor::turnOn()
{
  this->sensorState = SENSORSTATE::ON;
}

void IRSensor::turnOffFor(uint16_t duration)
{
  this->offDuration = duration;
  this->offTime = millis();
  this->sensorState = SENSORSTATE::OFF;
}

bool IRSensor::getBetween(uint8_t min, uint8_t max)
{
    uint8_t dist = this->getDistance();
    return (dist >= min && dist <= max);
}

bool IRSensor::getBelow(uint8_t limit)
{
    uint8_t dist = this->getDistance();
    if(!dist) 
    {
        return false;
    } 
    else 
    {
        return (dist < limit);
    }
}

bool IRSensor::getAbove(uint8_t limit)
{
  uint8_t dist = this->getDistance();
  return (dist > limit);
}


IRSensor::SensorRange IRSensor::isValid(uint16_t dist) 
{
    if (dist < MIN_IR_VALUE)
    {
        return ABOVE;
    }
    else if (dist > MAX_IR_VALUE)
    {
        return BELOW;
    }
	return (BETWEEN);
}
