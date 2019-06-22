#ifndef PARSER_H
#define PARSER_H

//Libraries
#include <Arduino.h>
/*
 * @brief parses the message with the given delimiter and returns the values in the array which is also a parameter
 * @param message The message to be parsed
 *        delimiter The delimiter at what the message has to be parsed
 *        returnArray The given array at what the function the values 
 * Example messsage = 100;50;25
 *         delimiter = ';'
 *         output = [100,50,25]
 */
void parseMessage(const String& message, char delimiter, uint8_t returnArray[]);

#endif
