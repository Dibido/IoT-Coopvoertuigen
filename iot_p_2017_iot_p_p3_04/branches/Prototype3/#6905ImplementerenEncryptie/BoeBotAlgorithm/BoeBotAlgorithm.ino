// Libraries
#include <Debug.h>
#include <Defines.h>
#include <MySensors.h>
#include <Xtea.h>
#include <math.h>

// Local
#include "Vehicle.h"

// Global variables
uint32_t previousTime = millis();
uint32_t previousTimeCom = millis();
Vehicle vehicle;

//Xtea setup
uint32_t key[4] = {KEY};
Xtea xtea(key);

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
  vehicle.handleMessage(xtea, message.getString(), message.sensor);
}

void registerVehicle()
{
  MyMessage msg(MY_MSG_BEGIN_VALUES);
  uint8_t values[REGISTER_MESSAGE_VALUE] = {MY_NODE_ID, REGISTER};
  //Encrypt the values of values
  xtea.encrypt(values);

  msg.setSensor(values[CHAR_POSITION]);
  String messageText = START + String(values[1]) + END;

  char tempCharArray[messageText.length()];
  //The +1 is to extend the temp array's length to match the length of the string
  messageText.toCharArray(tempCharArray, messageText.length() + 1);

  send(msg.set(tempCharArray));
}

void sendData()
{
  if (millis() - previousTimeCom >= DATA_SEND_INTERVAL)
  {
    uint8_t leftWheelSpeed = abs(vehicle.getDrivingControl().getLeftWheelSpeed() - STATIONARY);
    uint8_t rightWheelSpeed = abs(vehicle.getDrivingControl().getRightWheelSpeed() - STATIONARY);
    uint8_t frontDistance = vehicle.getFrontDistance();
    uint8_t leftDistance = vehicle.getLeftUltrasonicSensor().getDistance();
    uint8_t rightDistance = vehicle.getRightUltrasonicSensor().getDistance();

    //Make two arrays for the encryption
    uint8_t values[MAX_MESSAGE_LENGTH] = {SEND_DATA, leftWheelSpeed, rightWheelSpeed, frontDistance, leftDistance, rightDistance};

    //Encrypt the values and put them in encryptedValues array
    xtea.encryptValues(MAX_MESSAGE_LENGTH, values, values);

    String messageText = START + (String)values[1] + DELIMITER + (String)values[2] + DELIMITER
                         + (String)values[3] + DELIMITER + (String)values[4] + DELIMITER + (String)values[5]
                         + END;

    //Convert the string to char array to send it via MySensors
    char tempCharArray[messageText.length()];
    messageText.toCharArray(tempCharArray, messageText.length() + 1);

    MyMessage msg(MY_MSG_BEGIN_VALUES);
    msg.setSensor(values[CHAR_POSITION]);
    msg.set(tempCharArray);
    send(msg);
    //Reset the timer
    previousTimeCom = millis();
  }
}
