#ifndef DRIVINGCORRECTION_H_
#define DRIVINGCORRECTION_H_

// Local
#include <UltrasonicSensor.h>
#include <DrivingControl.h>
#include <Debug.h>

// Libraries
#include <Arduino.h>
#include <Defines.h>
#include <stdint.h>

/*
 * @brief : DrivingCorrection - Library to correct the vehicle path based on two walls
 * @author : Dibran
 * @date : 2018-04-26
 */
class DrivingCorrection
{
  public:
    DrivingCorrection(DrivingControl& control, UltrasonicSensor& lSensor, UltrasonicSensor& rSensor, uint8_t checkInterval, uint8_t margin);
    ~DrivingCorrection();

    /*
     * @brief Initialise the initial distances.
     * @brief Sets the initial values for the path to the currently measured values.
     */
    void init();
    /*
     * @brief Run the path correction algorithm
     * @brief The algorithm is only run if the checkInterval has passed
     */
    void run();
    /*
     * @brief Handle the correction of the path, correction is based on the diffences of both sensors
     */
    void handleCorrection();
    
    // Getters
    /*
     * @brief Read the current distances from the sensors into the curDist variables
     */
    void getDistances();
    /*
     * @brief Calculate the difference between two distances
     * @brief Is used to calculate the difference between the initial distance and the measured distance
     */
    int8_t getDistDifference(int8_t initDist, int8_t curDist);
	
	uint8_t getLeftInitDist();
	uint8_t getRightInitDist();
	
	
    // Setters
    /*
     * @brief Manually set new initial distances
     */
    void setInitDists(uint8_t leftDist, uint8_t rightDist);

  private:

    DrivingControl control;
    UltrasonicSensor leftDistSensor;
    UltrasonicSensor rightDistSensor;
    uint8_t initLeftDist;
    uint8_t initRightDist;
    uint8_t curLeftDist;
    uint8_t curRightDist;
    uint8_t checkInterval;
    uint8_t correctionMargin;
};

#endif /* DRIVINGCORRECTION_H_ */
