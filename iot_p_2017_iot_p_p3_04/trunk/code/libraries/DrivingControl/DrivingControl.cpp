// Libraries
#include <Debug.h>

// Local
#include "DrivingControl.h"

DrivingControl::DrivingControl(const Servo& leftWheel, const Servo& rightWheel, uint8_t accelerationSpeed, uint8_t decelerationSpeed) :
leftWheel(leftWheel),
rightWheel(rightWheel),
leftWheelSpeed(STATIONARY),
rightWheelSpeed(STATIONARY),
frontDistance(0),
accelerationSpeed(accelerationSpeed),
decelerationSpeed(decelerationSpeed)
{
}

DrivingControl::~DrivingControl()
{
}

void DrivingControl::changeSpeed(int16_t newSpeed)
{
	if (leftWheelSpeed < STATIONARY + newSpeed) // Acceleration
	{
		this->leftWheelSpeed += accelerationSpeed;	// Increase the left wheel speed to turn forward
		this->rightWheelSpeed -= accelerationSpeed;	// Decrease the right wheel speed because of the servo orientation
		this->leftWheel.writeMicroseconds(leftWheelSpeed);
		this->rightWheel.writeMicroseconds(rightWheelSpeed);
	}

	if (leftWheelSpeed > STATIONARY + newSpeed) // Deceleration
	{
		this->leftWheelSpeed -= decelerationSpeed;	// Decrease the left wheel speed because of the servo orientation
		this->rightWheelSpeed += decelerationSpeed;	// Increase the right wheel speed to slow down
		this->leftWheel.writeMicroseconds(leftWheelSpeed);
		this->rightWheel.writeMicroseconds(rightWheelSpeed);
	}
}

void DrivingControl::maneuver(uint16_t newLeftSpeed, uint16_t newRightSpeed) {

	this->leftWheelSpeed = newLeftSpeed;	// Increase the left wheel speed to turn forward
	this->rightWheelSpeed = newRightSpeed;	// Decrease the right wheel speed because of the servo orientation
	this->leftWheel.writeMicroseconds(this->leftWheelSpeed);
	this->rightWheel.writeMicroseconds(this->rightWheelSpeed);
}

// Getters
int16_t DrivingControl::getLeftWheelSpeed()
{
	return this->leftWheelSpeed;
}

// Getters
int16_t DrivingControl::getRightWheelSpeed()
{
	return this->rightWheelSpeed;
}

// Setters
void DrivingControl::setAccelerationSpeed(uint8_t accelerationSpeed)
{
	this->accelerationSpeed = accelerationSpeed;
}

void DrivingControl::setDecelerationSpeed(uint8_t decelerationSpeed)
{
	this->decelerationSpeed = decelerationSpeed;
}