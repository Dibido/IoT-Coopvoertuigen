#include "Xtea.h"

unsigned long key[4] = {0x01020304, 0x05060708, 0x090a0b0c, 0x0d0e0f00};
Xtea x(key);

void setup()
{
  Serial.begin(9600);
  while (!Serial) {

  }
  uint32_t v[] = {1234, 5678};
    x.encrypt(v);
    x.decrypt(v);
}

void loop()
{
}
