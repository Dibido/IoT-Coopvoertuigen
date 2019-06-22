void setup() {
  Serial.begin(115200);
  for (int i = 1; i <= 3; ++i) {
    Serial.print(String(i) + ";82;1;0;5;//\n");
    delay(10);
  }
}
int16_t counter = -200;
void loop() {
  for (int i = 1; i <= 3; ++i) {
    Serial.print(String(i) + ";68;1;0;5;/" + String(counter) + ";150;20;"+String(i*20)+";50/\n");
    delay(5000);
  }
  counter++;
  if (counter > 200) {
    counter = -200;
  }
}
