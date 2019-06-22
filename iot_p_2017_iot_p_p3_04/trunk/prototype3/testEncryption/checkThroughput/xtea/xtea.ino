#define BUFFERSIZE 200

#include "CircularBuffer.h"
#include "Xtea.h"
#include <Arduino.h>

#define NR_OF_RUNS 200


unsigned long key[4] = {0x01020304, 0x05060708, 0x090a0b0c, 0x0d0e0f00};
Xtea x(key);

void setup()
{

  uint32_t startTime = 0;
  uint32_t duration = 0;

  Serial.begin(9600);
  while (!Serial) {

  }
  CircularBuffer buffer;
  startBuffer(&buffer);

  Serial.print(F("N = "));
  Serial.println(NR_OF_RUNS);
  Serial.println(F("Xtea 128 bit key 64 bit message"));

  uint32_t v[] = {1234, 5678};
  for (int i = 0; i < NR_OF_RUNS; ++i)
  {
    startTime = micros();
    x.encrypt(v);
    duration = micros() - startTime;
    addValue(&buffer, duration);
  }

  Serial.println(F("Encrypt time (microseconds)"));
  printStats(&buffer, true);

  startBuffer(&buffer);

  for (int i = 0; i < NR_OF_RUNS; ++i)
  {
    startTime = micros();
    x.decrypt(v);
    duration = micros() - startTime;
    addValue(&buffer, duration);
  }

  Serial.println(F("Decrypt time (microseconds"));
  printStats(&buffer, true);

}

void loop()
{
}
