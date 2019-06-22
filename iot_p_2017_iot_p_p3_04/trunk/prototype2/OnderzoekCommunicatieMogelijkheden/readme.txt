MISO  =  6
MOSI  =  7
SCK   =  8

Channel = 4
The NODE_ID is the same as the CAR_ID, this to make sure there are no two cars with the same id.
The DATARATE is 1MB/s


// notes by Raymond
#define MY_DEBUG
#define MY_RADIO_NRF24

//Don't use for gateway
#define CAR_ID (1)
#define MY_NODE_ID (CAR_ID)

#define ID_DIST_SENSOR (0)
//Don't use for gateway

#define MY_SOFTSPI
#define MY_SOFT_SPI_MISO_PIN (6)   //MISO: 6
#define MY_SOFT_SPI_MOSI_PIN (7)   //MOSI: 7
#define MY_SOFT_SPI_SCK_PIN (8)    //SCK:  8

#define MY_RF24_CHANNEL (4)
#define MY_RF24_DATARATE (RF24_1MBPS)

#include <MySensors.h>

#define SKETCH_NAME "TestCar "
#define SKETCH_VERSION "v0.1"

other: https://www.mysensors.org/build/connect_radio

https://www.mysensors.org/apidocs-beta/group__SoftSpiSettingGrpPub.html#gac8fab125746041ca403ceb47b883c4b1

the "fullThrottleSending.log" is from the full throttle sending.
the "calmSending.log" is from the sending a message every 5 seconds for each car.