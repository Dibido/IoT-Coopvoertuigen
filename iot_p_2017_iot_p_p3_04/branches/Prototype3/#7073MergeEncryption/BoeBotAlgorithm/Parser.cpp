#include "Parser.h"

void parseMessage(const String& message, char delimiter, uint8_t returnArray[]) {
  //A temporary string to put the values of the not yet completely parsed message in
  String temp;
  //This is the index for returning into the array
  uint8_t index = 0;
  //Loop through the message
  for (int i = 0; i < message.length(); ++i) {
    //If the character in the message is the delimiter
    if (message.charAt(i) == delimiter) {
      //The temporary string is turned into an int and put into the array
      returnArray[index] = temp.toInt();
      index++;
      temp = "";
      //Else the character is added to the temporary string
    } else {
      temp += message.charAt(i);
    }
  }
  returnArray[index] = temp.toInt();
}
