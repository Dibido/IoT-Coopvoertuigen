#ifndef IRSENSOR_H_
#define IRSENSOR_H_

//library
#include <Arduino.h>
#include <stdint.h>

//defines
#define MAX_IR_VALUE 500
#define MIN_IR_VALUE 80

/**
 * @brief: IRSensor for measuring the distance to an object.
 * @author: Dibran
 */

class IRSensor 
{
  public:
    /**
     *  @brief Constructor for the IRSensor class
     *  @param sensorPin : the pin which the sensor is connected to
     */
    IRSensor(uint8_t sensorPin);

    /**
     *   @brief Destructor for the IRSensor class
     */
    ~IRSensor();
    /**
     *  Getter for the distance does not incorporate range checking
     *  @return the current distance, when the sensor is disabled it returns 0.
     */
    int16_t getDistance();
    /**
     *  @brief Check whether the sensor is enabled
     *  @return Whether the sensor is enabled
     */
    bool isEnabled();
    /**
     *  @brief Turn off the IRSensor (ignores the get)
     */
    void turnOff();
    /**
     *  @brief Turn on the IRSensor
     */
    void turnOn();
    /**
     *  @brief Turn the sensor off for a certain duration
     *  @param duration : duration to disable in milliseconds
     */
    void turnOffFor(uint16_t duration);
    /**
     *  @brief Check whether the read value is beteen an upper and lower bound.
     *  @param min : the lower bound
     *  @param max : the upper bound
     *  @return Whether the value is between the bounds
     */
    bool getBetween(uint8_t min, uint8_t max);

    /**
     * @brief Check whether the read value is below a certain limit
     * @param limit: the limit to check with
     * @return whether the value is below the limit
     */
    bool getBelow(uint8_t limit);
    /**
     * @brief Check whether the read value is above a certain limit
     * @param limit : the limit to check with
     * @return whether the value is above the limit
     */
    bool getAbove(uint8_t limit);

    enum SensorRange {BELOW, BETWEEN, ABOVE = 80};
    /**
      * @brief Check whether the raw analogRead value of the IR-sensor is between 80 and 500 https://www.eztronics.nl/webshop2/catalog/index.php?route=product/product&product_id=598
      * @param dist : The analog distance value that needs to be checked
      * @return SensorRange
      */
    SensorRange isValid(uint16_t dist);

	  
  private:
    /**
     *  Enum for the current state of the sensor
     */
    enum SENSORSTATE {OFF, ON};
    uint8_t sensorPin;
    SENSORSTATE sensorState;

    uint16_t offTime; //Time when the sensor was disabled in milliseconds
    uint16_t offDuration; //The current duration to wait for, when it is 0 it will not be checked
};

#endif
