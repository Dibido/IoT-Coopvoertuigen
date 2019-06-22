// Local
#include "SerialGateway.h"

// Libraries
// MySensors needs to be included here to prevent multiple definition errors from the MySensors library.
#include <MySensors.h>

/*
 *   The node id is always the first in the message. There is no separation character in front of this number.
 *   An example of the node id in a message is 1;0;0;0;//. In this example is 1 the node id.
 */
uint8_t getNodeNr(const String& received)
{
  //Temporary string to hold the nodeId
  String temp;
  for (size_t i = 0; i < received.length(); ++i)
  {
    if (received.charAt(i) != DELIMITER)
    {
      temp += received.charAt(i);
    }
    else
    {
      return temp.toInt();
    }
  }
  return NODE_ERROR;
}

/*
 * The child sensor is the second number is the message. 
 * There is a mysensors separation character in front and back of the number.
 * The number is turned into a character in this function
 * Example of a child sensor: 0;1;0;0;//. Where 1 is the child sensor
 */
char getChildSensor(const String& received)
{
  //Temporary string to hold the childsensorId
  String temp;
  for (size_t i = received.indexOf(DELIMITER) + 1; i < received.length(); ++i)
  {
    if (received.charAt(i) != DELIMITER)
    {
      temp += received.charAt(i);
    } else
    {
      return (char)temp.toInt();
    }
  }
  return CHILD_SENSOR_ERROR;
}

/*
 * The payload is the data that the user put in the message.
 * This is surrounded by a user separation character, which is defined in the .h file.
 */
String getPayload(const String& received)
{
  //Temporary string to hold the payload
  String temp = String(START);
  for (size_t i = received.indexOf(START) + 1; i < received.length(); ++i)
  {
    if (received.charAt(i) != END)
    {
      temp += received.charAt(i);
    } else
    {
      temp += received.charAt(i);
      return temp;
    }
  }
  return PAYLOAD_ERROR;
}

void sendMessage(const uint8_t& nodeId, const char& childSensor, const String& payLoad)
{
  MyMessage msg(1, 1);
  msg.setDestination(nodeId);
  msg.setSensor(childSensor);
  char t[payLoad.length() + 1];
  //Convert a String to a char array, because MySensors only sends a charArray and not a String
  payLoad.toCharArray(t, payLoad.length() + 1);
  send(msg.set(t));
}
