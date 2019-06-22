#ifndef VEHICLE_H
#define VEHICLE_H

// Libraries
#include <DrivingControl.h>
#include <DistanceSensor.h>
#include <Servo.h>
#include <Arduino.h>

#define ACCELERATION_SPEED 100
#define DECELERATION_SPEED 25
#define LEFT_PIN 11
#define RIGHT_PIN 12

#define MAX_DIST 15

class Vehicle
{
    public:
        Vehicle();
        ~Vehicle();
        void drive(DistanceSensor& ds, DrivingControl& dc);

    private:
        
};

#endif /* VEHICLE_H */
