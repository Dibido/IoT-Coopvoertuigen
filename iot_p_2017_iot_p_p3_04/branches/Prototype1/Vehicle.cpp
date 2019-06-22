// Local
#include "Vehicle.h"

#define DEBUG_MODE

//Libraries
#include <Debug.h>

Vehicle::Vehicle()
{}

Vehicle::~Vehicle()
{
}

void Vehicle::drive(DistanceSensor& ds, DrivingControl& dc)
{

    uint8_t frontDistance = ds.getDistance();
//    dc.changeSpeed(100);
//    debugln(frontDistance);
//    delay(200);

    
    if (frontDistance < MAX_DIST)
    {
        debugln("Stop");
        dc.changeSpeed(0);
    }
    else if (frontDistance > MAX_DIST)
    {
        debugln("Go");
        dc.changeSpeed(100);
    }
}
