#ifndef DEFINES_H
#define DEFINES_H

// BoeBot Algorithm
#define REACTION_SPEED 		100
#define DATA_SEND_INTERVAL	2000

// Vehicle
#define ACCELERATION_SPEED 			5
#define DECELERATION_SPEED 			20
#define DRIVING_SPEED 				100
#define VEHICLE_TOP_DRIVING_SPEED	200
#define MAX_DIST 					16
#define SENSOR_PIN 					A0
#define LEFT_WHEEL_PIN 				11
#define RIGHT_WHEEL_PIN 			12
#define L_ECHO_PIN 					5
#define R_ECHO_PIN 					3
#define L_TRIG_PIN 					4
#define R_TRIG_PIN 					2
#define VEHICLE_FOLLOW_DIST 		60
#define VEHICLE_MAX_FOLLOW_DIST 	70
#define VEHICLE_EXIT_DIST			40
#define MIN_VEHICLE_EXIT_DIST		50

#define STOP_EXITING_TIMER 5000
#define VEHICLE_BLINKING_TIMER 500
#define MIN_EXIT_DIST 30

#define VEHICLE_LEFT_LED			A0
#define VEHICLE_RIGHT_LED			A1

// Merging
#define MERGING_CARWIDTH 					10
#define MERGING_STANDARD_MEASUREMENT_MARGIN	1
#define MERGING_GAPTIME_MARGIN 				1500
#define MERGING_DIFF_COUNT 					10
#define MERGING_CHANGE_COUNT 10

// MySensors
// If the gateway is defined get gateway defines
#ifdef SERIAL_GATEWAY
#define MY_RF24_PA_LEVEL RF24_PA_MAX
#define MY_GATEWAY_SERIAL
//The error codes for getters in the gateway
#define NODE_ERROR 0
#define CHILD_SENSOR_ERROR '0'
#define PAYLOAD_ERROR "0"
// Else get the vehicle defines
#else
#define MY_NODE_ID 1
#define MY_RF24_PA_LEVEL RF24_PA_LOW
#endif

#define MY_SOFTSPI
#define MY_SOFT_SPI_MISO_PIN (6)   //MISO: 6
#define MY_SOFT_SPI_MOSI_PIN (7)   //MOSI: 7
#define MY_SOFT_SPI_SCK_PIN (8)    //SCK:  8
#define MY_RADIO_NRF24
#define MY_RF24_CHANNEL 4
#define MY_MSG_BEGIN_VALUES 1,1

// Vehicle communication protocol
#define START 		'/'
#define END 		'/'
#define DELIMITER	';'
#define VEHICLE_MAX_MESSAGE_LENGTH 3
#define CHAR_POSITION 0
#define REGISTER_MESSAGE_VALUE 2 //The length of an register message to the gateway

// Debug

//#define MY_DEBUG
#define DEBUG_MODE

// Ultrasonic Sensor
#define DELAY_START_PULSE 	2
#define DELAY_END_PULSE		10

// Driving Control
#define STATIONARY 			1500
#define STD_MOVING_SPEED_L	1600
#define STD_MOVING_SPEED_R 	1400

#define EXIT_MOVING_SPEED_L 1640
#define EXIT_MOVING_SPEED_R 1440

// Driving Correction
#define CORRECTION_SPEED 30

//Time Of Flight
#define TOF_TIMEOUT 			500
#define TOF_RATE_LIMIT 			0.1
#define TOF_PULSE_PRE_RANGE 	18
#define TOF_PULSE_FINAL_RANGE	14
#define TOF_TIMING 				200000

//Xtea 
#define KEY_LENGTH 4
#define KEY 0x01020304, 0x05060708, 0x090a0b0c, 0x0d0e0f00

#endif /* DEFINES_H */
