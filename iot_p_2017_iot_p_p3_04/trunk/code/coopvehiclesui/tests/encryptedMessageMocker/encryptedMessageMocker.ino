#include <Xtea.h>

uint32_t key[4] = {0x01020304, 0x05060708, 0x090a0b0c, 0x0d0e0f00};
Xtea x(key);

uint8_t values[6] = {68, 100, 100, 25, 15, 16};
uint8_t encrypted[6];
uint8_t r[2] = { 82, 1 };
uint8_t regE[2];

void setup() {
  Serial.begin(115200);
  //  uint8_t decrypted[6];

  encryptValues(x, 6, values, encrypted);
  encryptValues(x, 2, r, regE);
  //  Serial.println("----");
  //  for (int i = 0; i < 6; ++i) {
  //    Serial.println(values[i]);
  //  }
  //  Serial.println("-------");
  //  for (int i = 0; i < 6; ++i) {
  //    Serial.println(encrypted[i]);
  //  }
  //  Serial.println("-------");
  //  decryptValues(x,6,encrypted, decrypted);
  //  for (int i = 0; i < 6; ++i) {
  //    Serial.println(decrypted[i]);
  //  }

  delay(1000);

  Serial.print("1;");
  Serial.print(regE[0]);
  Serial.print(";1;0;5;/");
  Serial.print(regE[1]);
  Serial.print("/\n");

  Serial.print("1;");
  Serial.print(encrypted[0]);
  Serial.print(";1;0;5;/");
  Serial.print(encrypted[1]);
  Serial.print(";");
  Serial.print(encrypted[2]);
  Serial.print(";");
  Serial.print(encrypted[3]);
  Serial.print(";");
  Serial.print(encrypted[4]);
  Serial.print(";");
  Serial.print(encrypted[5]);
  Serial.print("/\n");
}

void loop() {
  delay(5000);

  Serial.print("1;");
  Serial.print(encrypted[0]);
  Serial.print(";1;0;5;/");
  Serial.print(encrypted[1]);
  Serial.print(";");
  Serial.print(encrypted[2]);
  Serial.print(";");
  Serial.print(encrypted[3]);
  Serial.print(";");
  Serial.print(encrypted[4]);
  Serial.print(";");
  Serial.print(encrypted[5]);
  Serial.println("/");
}
