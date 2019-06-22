//#define MY_DEBUG

#define MY_RADIO_NRF24

#define MY_NODE_ID 1

#define MY_RF24_CHANNEL 6

#define MY_SOFTSPI
#define MY_SOFT_SPI_MISO_PIN (6)   //MISO: 6
#define MY_SOFT_SPI_MOSI_PIN (7)   //MOSI: 7
#define MY_SOFT_SPI_SCK_PIN (8)    //SCK:  8


#include <MySensors.h>

MyMessage msg(1, V_STATUS);

void setup() {
}
int counter= 0;
void loop() {
  String sendMessage = "/";
  sendMessage+=String(counter);
  sendMessage+=";150;20;40;50/";
  char temp[sendMessage.length()];
  sendMessage.toCharArray(temp, sendMessage.length() + 1);
  msg.setSensor('D');
  send(msg.set(temp));
  Serial.println(sendMessage);
  counter++;
  if(counter>200){
    counter =-200;
  }
  
  delay(1000);
}

void receive(const MyMessage& message) {
  switch (message.sensor) {
    case 's':
      Serial.println("STOP DRIVING");
      break;
    case 'r':
      Serial.println("Registered");
      break;
    default:
      Serial.println((char)message.sensor);
      Serial.println(message.getString());
  }
}

