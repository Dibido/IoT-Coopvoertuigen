#include "initBot.h"
#include "moveBot.h"

void setup() {
  Serial.begin(9600);
  setupBot();
  goForward(100);   //Goes forwards at a speed of 100 until any other maneuver is called or even stopManeuver to stop the bot.
}

void loop() {
  
}
