import processing.serial.*;
Serial Port;

final int baudRate=9600;
final char separationChar = '|';

void setup() {
  size(500, 500);
  background(0);
  println("Serial deviced: ");
  for(String s:Serial.list()){
    println(s);
  }
  println("-------------");
  Port=new Serial(this, Serial.list()[Serial.list().length-1], baudRate);
}

int nrOfCars = 1;
int speed = 0;
String addCarString = "Car";
String addSpeedString = "Speed";
String deleteString = "Delete";
int speedStep = 10;

int carMargin = 20;
int speedX = 70;

void draw() {
  background(0);
  if (Port.available()>0) {
    String reading = Port.readStringUntil('|');
    println(reading);
    reading = reading.substring(0,reading.length()-1);
    if (reading.equals(addCarString)) {
      nrOfCars++;
    } else if (reading.equals(addSpeedString)) {
      speed+=speedStep;
    }else if (reading.equals(deleteString)){
      nrOfCars--;
    }
  }
  for (int i=0; i<nrOfCars; ++i) {
    text("Car nr: "+i, 10, carMargin+carMargin*i);
    text("Speed: "+speed, speedX, carMargin+carMargin*i);
  }
}
