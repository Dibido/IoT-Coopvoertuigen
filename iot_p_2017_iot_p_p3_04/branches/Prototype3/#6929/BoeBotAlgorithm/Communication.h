#ifndef COMMUNICATION_H
#define COMMUNICATION_H

//Internal libraries
#include <Debug.h>

// External libraries
#include <stdint.h>
#include <Arduino.h>

extern bool vehicleRegistered;
extern uint64_t previousTimeCom;

//#define REGISTER_CHARACTER 'R'
//#define DATA_CHARACTER 'D'

// Send message types
enum sendChar
{
    REGISTER = 'R', SEND_DATA = 'D'
};

// Receive message types
enum receivedChar
{
    VEHICLE_REGISTERED = 'r',
    START_DRIVING = 'd',
    START_MERGING = 'm', 
    HEARTBEAT = 'h', 
    EXIT_LANE = 'e', 
    STOP_DRIVING = 's'
};

// MySensors Defines
//#define MY_DEBUG // Activate MySensors debug mode
#define MY_SOFTSPI
#define MY_SOFT_SPI_MISO_PIN (6)   //MISO: 6
#define MY_SOFT_SPI_MOSI_PIN (7)   //MOSI: 7
#define MY_SOFT_SPI_SCK_PIN (8)    //SCK:  8
#define MY_RADIO_NRF24
#define MY_RF24_CHANNEL 6
#define MY_NODE_ID 1

// Interval between sending data
// Default = 2000
#define DATA_SEND_INTERVAL 2000

/**
    @brief Sends a register message to the checkpoint
**/
void registerVehicle();

/**
    @brief Sends the given vehicle data to the checkpoint
    @param leftSpeed Speed of the left wheel
    @param rightSpeed Speed of the right wheel
    @param frontDist Distance measured on the front of the Boe-Bot
    @param leftDist Distance measured on the left of the Boe-Bot
    @param rightDist Distance measure on the right of the Boe-Bot
**/
void sendData(uint8_t leftSpeed, uint8_t rightSpeed, uint8_t frontDist, uint8_t leftDist, uint8_t rightDist);

#endif /* COMMUNICATION_H */
