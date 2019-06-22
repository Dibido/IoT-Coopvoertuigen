#ifndef ULTRASONICSENSOR_H_
#define ULTRASONICSENSOR_H_

// Library
#include <Arduino.h>
#include <stdint.h>

#include <Debug.h>

// Defines
#define SPEED_OF_SOUND 0.034 //The speed of sound in us/cm (microseconds per centimeter)

/**
 * @brief: UltrasonicSensor for measuring the distance to an object.
 * @author: Brandon
 */

class UltrasonicSensor 
{
  public:
    /**
	 *  @author: Brandon
     *  @brief Constructor for the UltrasonicSensor class
     *  @param triggerPin : the pin which sends a high frequency sound wave
     *  @param echoPin : the pin which acts as a receiver
     */
    UltrasonicSensor(uint8_t triggerPin, uint8_t echoPin);

    /**
	 *	 @author: Brandon
     *   @brief Destructor for the UltrasonicSensor class
     */
    virtual ~UltrasonicSensor();
    /**
     *  @author: Brandon
     *  @return the current distance, when the sensor is disabled it returns 0.
     */
    uint8_t getDistance();

	  
  private:
    uint8_t triggerPin;
	uint8_t echoPin;

    uint16_t offTime; //Time when the sensor was disabled in milliseconds
    uint16_t offDuration; //The current duration to wait for, when it is 0 it will not be checked
};

#endif /* ULTRASONICSENSOR_H_ */
