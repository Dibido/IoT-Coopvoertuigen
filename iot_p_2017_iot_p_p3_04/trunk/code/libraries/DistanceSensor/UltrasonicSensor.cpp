// Libraries
#include <Defines.h>

// Local
#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(uint8_t triggerPin, uint8_t echoPin) : triggerPin(triggerPin), echoPin(echoPin)
{
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

UltrasonicSensor::~UltrasonicSensor()
{
}

uint8_t UltrasonicSensor::getDistance()
{
	digitalWrite(this->triggerPin, LOW);
	delayMicroseconds(DELAY_START_PULSE);

	digitalWrite(this->triggerPin, HIGH);
	delayMicroseconds(DELAY_END_PULSE);
	digitalWrite(this->triggerPin, LOW);

	uint32_t duration = pulseIn(this->echoPin, HIGH);
	return duration * SPEED_OF_SOUND / 2;	//To calculate the total distance in cm the SPEED_OF_SOUND in us/cm is used. To calculate the one-way distance the total distance needs to be divided by 2
}

