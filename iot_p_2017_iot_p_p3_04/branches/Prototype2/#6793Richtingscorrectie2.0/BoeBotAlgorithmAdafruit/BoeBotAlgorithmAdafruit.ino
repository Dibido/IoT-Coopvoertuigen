// Defines
#define DEBUG_MODE
#define REACTION_SPEED 100

// Local
#include "Vehicle.h"

//Libraries
#include <Debug.h>

uint64_t previousTime = millis();
Vehicle vehicle;

void setup()
{
    Serial.begin(9600);
    debugln("Serial started!");
    vehicle.vehicleSetup();
}

void loop()
{
    uint64_t currentTime = millis();
    
    if (millis() - previousTime >= REACTION_SPEED)
    {
        previousTime = currentTime;
        vehicle.drive();
    }
}
