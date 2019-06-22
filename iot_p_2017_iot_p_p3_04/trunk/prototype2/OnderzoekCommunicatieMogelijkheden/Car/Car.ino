#define MY_DEBUG
#define MY_RADIO_NRF24

#define CAR_ID (3)
#define MY_NODE_ID (CAR_ID)

#define ID_DIST_SENSOR_FRONT (0)

#define MY_SOFTSPI
#define MY_SOFT_SPI_MISO_PIN (6)   //MISO: 6
#define MY_SOFT_SPI_MOSI_PIN (7)   //MOSI: 7
#define MY_SOFT_SPI_SCK_PIN (8)    //SCK:  8

#define MY_RF24_CHANNEL (4)
#define MY_RF24_DATARATE (RF24_1MBPS)

#include <MySensors.h>

#define SKETCH_NAME "TestCar "
#define SKETCH_VERSION "v0.1"

uint32_t currentMillis = 0;
uint32_t previousSendMillis = 0;
uint32_t timeBetweenSend = 5000;  //5 seconds

MyMessage distFrontMsg(ID_DIST_SENSOR_FRONT, V_VAR1);



void sendMessage(MyMessage& msg, char* content) {
  send(msg.set(content));
}

void loopWithDelay(uint32_t delay) {
  currentMillis = millis();

  if (currentMillis - previousSendMillis >= delay) {
    sendMessage(distFrontMsg, "This is a test message.");
    previousSendMillis = currentMillis;
  }
}

void loopWithoutDelay() {
  sendMessage(distFrontMsg, "This is a test message.");
}


void presentation() {
  sendSketchInfo(SKETCH_NAME, SKETCH_VERSION);

  present(ID_DIST_SENSOR_FRONT, S_CUSTOM, "Distance sensor front");
}

void setup() {

}

void loop() {
  loopWithDelay(timeBetweenSend);
//  loopWithoutDelay();
}

