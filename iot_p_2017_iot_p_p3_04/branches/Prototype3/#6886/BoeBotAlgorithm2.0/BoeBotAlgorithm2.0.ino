// Defines
//#define DEBUG_MODE
#define REACTION_SPEED 100
#define DATA_SEND_INTERVAL 2000

#define MY_SOFTSPI
#define MY_SOFT_SPI_MISO_PIN (6)   //MISO: 6
#define MY_SOFT_SPI_MOSI_PIN (7)   //MOSI: 7
#define MY_SOFT_SPI_SCK_PIN (8)    //SCK:  8
#define MY_RADIO_NRF24
#define MY_RF24_CHANNEL 4
#define MY_NODE_ID 1

//Libraries
#include <Debug.h>
#include <MySensors.h>

// Local
#include "Vehicle.h"

// Global variables
uint32_t previousTime = millis();
uint32_t previousTimeCom = millis();
Vehicle vehicle;

void setup()
{
  vehicle.registerVehicle();
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

void sendData()
{
  uint8_t leftWheelSpeed = abs(vehicle.getDrivingControl().getLeftWheelSpeed() - 1500);
  uint8_t rightWheelSpeed = abs(vehicle.getDrivingControl().getRightWheelSpeed() - 1500);
  uint8_t frontDistance = vehicle.getFrontDistance();
  uint16_t leftDistance = vehicle.getLeftUltrasonicSensor().getDistance();
  uint16_t rightDistance = vehicle.getRightUltrasonicSensor().getDistance();

  if (millis() - previousTimeCom >= DATA_SEND_INTERVAL)
  {
    previousTimeCom = millis();

    String messageText = "/" + (String)leftWheelSpeed + ";" + (String)rightWheelSpeed + ";" + (String)frontDistance + ";" + (String)leftDistance + ";" + (String)rightDistance + "/";

    char tempCharArray[messageText.length()];
    messageText.toCharArray(tempCharArray, messageText.length() + 1);

    debugln(tempCharArray);

    MyMessage msg(1, 1);
    msg.setSensor('D');     // Set child sensor to 'D' from data
    msg.set(tempCharArray);
    send(msg);
  }
}

void registerVehicle()
{
  MyMessage msg(1, 1);
  msg.setSensor('R');     // Set child sensor to 'R' from register
  send(msg.set(F("//")));
}
