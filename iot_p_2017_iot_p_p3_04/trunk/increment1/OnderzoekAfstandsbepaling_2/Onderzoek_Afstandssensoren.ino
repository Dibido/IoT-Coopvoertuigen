/*
  Ultrasonic Sensor HC-SR04 and Arduino Tutorial

  Crated by Dejan Nedelkovski,
  www.HowToMechatronics.com

*/

#define BUFFERSIZE 100
#include "CircularBuffer.h"

#define N 100

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

CircularBuffer buffer;
const int sensorpin = A0;                 // analog pin used to connect the sharp sensor
float val = 0;                 // variable to store the values from sensor(initially zero)

void testUltraSonicSensor(uint16_t n){
  startBuffer(&buffer);

  long duration;
  float distance;

  for (uint16_t i = 0; i < n; ++i){
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    distance = duration * 0.034 / 2;

    addValue(&buffer, distance);
  }

  // Serial.println("Ultrasonic Sensor");
  Serial.print("n = ");
  Serial.println(n);
  printStats(&buffer, "Ultrasonic Sensor\nAll values in cm", true);

}

void testSharpSensor(uint16_t n){
  startBuffer(&buffer);

    for (uint16_t i = 0; i < n; ++i){
        val = analogRead(sensorpin);       // reads the value of the sharp sensor
        float IRdistance = 4800/(val - 20);
        addValue(&buffer, IRdistance);
    }

    Serial.print("n = ");
    Serial.println(n);
    printStats(&buffer, "Sharp Sensor\nAll values in cm", true);


}

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200); // Starts the serial communication
  pinMode(7, INPUT);
}

void loop() {
  if (Serial.available()){
    char c = Serial.read();
    Serial.write(c);
    if (c == '\n'){
      Serial.println("Testing...");
        testSharpSensor(N);
        testUltraSonicSensor(N);
    }
  }
}
