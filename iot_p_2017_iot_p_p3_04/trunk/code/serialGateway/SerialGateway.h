#ifndef SERIALGATEWAY_H
#define SERIALGATEWAY_H

//Define to trigger the gateway defines
#define SERIAL_GATEWAY

//Libraries
#include <Arduino.h>
#include <Defines.h>

/**
 * Get the Node id from a received string
 * received - The complete message in the format that is given in the communicationprotocol, https://sasscm.han.nl/redmine/projects/iot_p_2017_iot_p_p3_04/wiki/03_Detailed_Design_Description_-_SDD#Communicatieprotocol-Boe-Bots-en-Controlepost
 */
uint8_t getNodeNr(const String& received);

/**
 * Get the child sensor char from a received string
 * received - The complete message in the format that is given in the communicationprotocol, https://sasscm.han.nl/redmine/projects/iot_p_2017_iot_p_p3_04/wiki/03_Detailed_Design_Description_-_SDD#Communicatieprotocol-Boe-Bots-en-Controlepost
 */
char getChildSensor(const String& received);

/**
 * Get the users string from a received string
 * received - The complete message in the format that is given in the communicationprotocol, https://sasscm.han.nl/redmine/projects/iot_p_2017_iot_p_p3_04/wiki/03_Detailed_Design_Description_-_SDD#Communicatieprotocol-Boe-Bots-en-Controlepost
 */
String getPayload(const String& received);

/**
 * Send a message to a specific node with a child sensor and payload
 * nodeId - This is the node id where the message has to go to. 
 * childSensor - This is the messagetype. With this messagetype the message can be recognised as a startDriving for example
 *               This is specified in https://sasscm.han.nl/redmine/projects/iot_p_2017_iot_p_p3_04/wiki/03_Detailed_Design_Description_-_SDD#Communicatieprotocol-Boe-Bots-en-Controlepost
 * payLoad - This is the data the user wants to send with the message. This is specified in  https://sasscm.han.nl/redmine/projects/iot_p_2017_iot_p_p3_04/wiki/03_Detailed_Design_Description_-_SDD#Communicatieprotocol-Boe-Bots-en-Controlepost
 */
void sendMessage(const uint8_t& nodeId, const char& childSensor, const String& payLoad);

#endif /* SERIALGATEWAY_H */
