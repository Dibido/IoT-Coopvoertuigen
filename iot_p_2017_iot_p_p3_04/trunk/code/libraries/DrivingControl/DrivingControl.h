#ifndef DRIVINGCONTROL_H
#define DRIVINGCONTROL_H

// Libraries
#include <stdint.h>
#include <Servo.h>
#include <Defines.h>

class DrivingControl
{
    public:
              
		/**
		* @brief Constructor for the DrivingControl class
		* @param leftWheel
		* @param rightWheel
		**/        
        DrivingControl(const Servo& leftWheel, const Servo& rightWheel, uint8_t accelerationSpeed, uint8_t decelerationSpeed);
        
		/**
		* @brief Destructor for the DrivingControl class
		**/
        virtual ~DrivingControl();
        
		/**
		* @brief Gradually changes the speed of both wheels to newSpeed
		* @param newSpeed The new speed that the Boe-Bot gradually works towards
		**/
        void changeSpeed(int16_t newSpeed);

		/**
		* @brief Maneuver the bot by manually changing the current speed for each wheel
		* @param newLeftSpeed The new speed value for the left wheel
		* @param newRightSpeed The new speed value for the right wheel
		**/
		void maneuver(uint16_t newLeftSpeed, uint16_t newRightSpeed);

        // Getters
        int16_t getLeftWheelSpeed();
        int16_t getRightWheelSpeed();

        // Setters
        void setAccelerationSpeed(uint8_t accelerationSpeed);
        void setDecelerationSpeed(uint8_t decelerationSpeed);

    private:
        Servo leftWheel;            // Servo of the left wheel
        Servo rightWheel;           // Servo of the right wheel
        int16_t leftWheelSpeed;     // Speed of the left wheel
        int16_t rightWheelSpeed;    // Speed of the right wheel
        uint16_t frontDistance;     // The distance in front of the bot measured by the distance sensor
        uint8_t accelerationSpeed;  // The speed at which the bot accelerates. The higher the value, the faster the acceleration.
        uint8_t decelerationSpeed;  // The speed at which the bot decelerates. The higher the value, the faster the deceleration.

        // Gradually changes the speed of the given wheel
        void changeWheelSpeed(Servo wheel, int16_t oldSpeed, int16_t newSpeed);
};

#endif /* DRIVINGCONTROL_H */