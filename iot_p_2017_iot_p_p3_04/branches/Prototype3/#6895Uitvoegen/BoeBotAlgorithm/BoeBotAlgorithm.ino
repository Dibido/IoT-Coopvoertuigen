// Libraries
#include <Debug.h>
#include <Defines.h>
#include <MySensors.h>

// Local
#include "Vehicle.h"

// Global variables
uint32_t previousTime = millis();
uint32_t previousTimeCom = millis();
Vehicle vehicle;

void setup()
{
  registerVehicle();
  vehicle.vehicleSetup();
}

void loop()
{
  uint32_t currentTime = millis();
  if (millis() - previousTime >= REACTION_SPEED)
  {
    previousTime = currentTime;
    vehicle.drive();
    sendData();
  }
}

void receive(const MyMessage &message)
{
  vehicle.handleMessage(message.getString(), message.sensor);
}

void registerVehicle()
{
  MyMessage msg(1, 1);
  msg.setSensor(REGISTER);     // Set child sensor to 'R' from register
  send(msg.set("//"));
}

void sendData()
{
  uint8_t leftWheelSpeed = abs(vehicle.getDrivingControl().getLeftWheelSpeed() - STATIONARY);
  uint8_t rightWheelSpeed = abs(vehicle.getDrivingControl().getRightWheelSpeed() - STATIONARY);
  uint8_t frontDistance = vehicle.getFrontDistance();
  uint16_t leftDistance = vehicle.getLeftUltrasonicSensor().getDistance();
  uint16_t rightDistance = vehicle.getRightUltrasonicSensor().getDistance();

  if (millis() - previousTimeCom >= DATA_SEND_INTERVAL)
  {
    previousTimeCom = millis();

    String messageText = START + (String)leftWheelSpeed + DELIMITER + (String)rightWheelSpeed + DELIMITER + (String)frontDistance + DELIMITER + (String)leftDistance + DELIMITER + (String)rightDistance + END;

    char tempCharArray[messageText.length()];
    messageText.toCharArray(tempCharArray, messageText.length() + 1);

    MyMessage msg(1, 1);
    msg.setSensor('D');     // Set child sensor to 'D' from data
    msg.set(tempCharArray);
    send(msg);
  }
}

