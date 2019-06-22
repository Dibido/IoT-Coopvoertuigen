#include <Xtea.h>

uint32_t key[4] = {0x01020304, 0x05060708, 0x090a0b0c, 0x0d0e0f00};
Xtea x(key);

void setup() {
  Serial.begin(115200);

  uint8_t values[6] = {2, 100, 100, 25, 15, 16};
  uint8_t encrypted[6];
  uint8_t decrypted[6];

  encryptValues(x,6,values, encrypted);
  Serial.println("----");
  for (int i = 0; i < 6; ++i) {
    Serial.println(values[i]);
  }
  Serial.println("-------");
  for (int i = 0; i < 6; ++i) {
    Serial.println(encrypted[i]);
  }
  Serial.println("-------");
  decryptValues(x,6,encrypted, decrypted);
  for (int i = 0; i < 6; ++i) {
    Serial.println(decrypted[i]);
  }
}

void loop() {}



