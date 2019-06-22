void setup() {
  Serial.begin(9600);

}
int nr=0;
void loop() {
  Serial.print("Car|");
  nr++;
  delay(5000);
  Serial.print("Speed|");
  delay(5000);
  if(nr%5==0){
    Serial.print("Delete|");
    delay(5000);
  }

}
