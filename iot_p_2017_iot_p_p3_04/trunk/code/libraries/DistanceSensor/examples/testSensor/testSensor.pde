#include <DistanceSensor.h>

DistanceSensor sensor(A0);

#define IRSENSOR_PIN A0

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(sensor.getDistance());
  Serial.println(sensor.getBetween(5, 10));
  Serial.println(sensor.getBelow(10));
  Serial.println(sensor.getAbove(10));
  Serial.println(sensor.isEnabled());
  sensor.turnOff();
  Serial.println(sensor.isEnabled());
  sensor.turnOn();
  sensor.turnOffFor(50);
  delay(25);
  Serial.println(sensor.isEnabled());
  delay(30);
  Serial.println(sensor.isEnabled());
  delay(50);
}
