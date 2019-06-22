//Local
#include "SerialGateway.h"
#include <Debug.h>

void loop()
{
  if (Serial.available())
  {
    String receivedString(Serial.readString());
    uint8_t nodeId = getNodeNr(receivedString);
    char childSensor = getChildSensor(receivedString);
    String payload = getPayload(receivedString);
    if (nodeId != NODE_ERROR && childSensor != CHILD_SENSOR_ERROR && payload != PAYLOAD_ERROR)
    {
      sendMessage(getNodeNr(receivedString), getChildSensor(receivedString), getPayload(receivedString));
    } else
    {
      debug(F("0;255;0;0;0;An error has occured. The message "));
      debug(receivedString.substring(0,receivedString.length()-1));
      debugln(F(" doesn't match the protocol."));
    }
  }
}
