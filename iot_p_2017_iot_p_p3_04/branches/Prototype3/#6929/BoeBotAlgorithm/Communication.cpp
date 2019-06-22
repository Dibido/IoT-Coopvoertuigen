// Local
#include "Communication.h"

// Library
#include <MySensors.h>

// Global variables
bool vehicleRegistered = false;
uint64_t previousTimeCom = millis();

void registerVehicle()
{
    MyMessage msg(1, 1);
    msg.setSensor(REGISTER);     // Set child sensor to 'R' from register
    send(msg.set("//"));
}

void sendData(uint8_t leftSpeed, uint8_t rightSpeed, uint8_t frontDist, uint8_t leftDist, uint8_t rightDist)
{
    if (millis() - previousTimeCom >= DATA_SEND_INTERVAL)
    {
        previousTimeCom = millis();
        debugln("Sending data");

        String messageText = "/100;100;10;10;10/";
        // TODO
        // "/" + leftSpeed + ";" + rightSpeed + ";" + frontDist + ";" + leftDist + ";" + rightDist;

        char tempCharArray[messageText.length()];
        messageText.toCharArray(tempCharArray, messageText.length() + 1);

        MyMessage msg(1, 1);
        msg.setSensor(SEND_DATA);     // Set child sensor to 'D' from data
        msg.set(tempCharArray);
        send(msg);    // Mocked data
    }
}

void receive(const MyMessage &message)
{
    debug("Message received: ");
    debugln(char(message.sensor));

    switch (message.sensor) // The childSensorId is used to indicate the message type
    {
        case VEHICLE_REGISTERED:
            debugln(F("Vehicle registered!"));
            vehicleRegistered = true;
            break;

        case START_DRIVING:
            debug(F("startDriving message received: "));
            debugln(message.getString());
            break;

        case START_MERGING:
            debug(F("startMerging message received: "));
            debugln(message.getString());
            break;

        case HEARTBEAT:
            debug(F("heartbeat message received: "));
            debugln(message.getString());
            break;

        case EXIT_LANE: 
                debug(F("exitLane message received: "));
            debugln(message.getString());
            break;

        case STOP_DRIVING:
            debug(F("stopDriving message received: "));
            debugln(message.getString());
            break;

        default:
            debugln(F("Error in communication.cpp: unknown message type"));
            break;
    }
}
