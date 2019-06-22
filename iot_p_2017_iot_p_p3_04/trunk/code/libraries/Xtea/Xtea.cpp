/*
  Xtea.cpp - Xtea encryption/decryption
  Written by Frank Kienast in November, 2010
*/

#include <Arduino.h>

#include "Xtea.h"

#define NUM_ROUNDS 32

Xtea::Xtea(uint32_t key[4])
{
  _key[0] = key[0];
  _key[1] = key[1];
  _key[2] = key[2];
  _key[3] = key[3];
}

void Xtea::encrypt(uint8_t v[2])
{
  uint8_t v0 = v[0], v1 = v[1];
  uint32_t sum = 0, delta = 0x9E3779B9;

  for (uint16_t i = 0; i < NUM_ROUNDS; i++)
  {
    v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + _key[sum & 3]);
    sum += delta;
    v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + _key[(sum >> 11) & 3]);
  }

  v[0] = v0; v[1] = v1;
}

void Xtea::decrypt(uint8_t v[2])
{
  uint8_t v0 = v[0], v1 = v[1];
  uint32_t delta = 0x9E3779B9, sum = delta * NUM_ROUNDS;

  for (uint16_t i = 0; i < NUM_ROUNDS; i++)
  {
    v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + _key[(sum >> 11) & 3]);
    sum -= delta;
    v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + _key[sum & 3]);
  }

  v[0] = v0; v[1] = v1;
}

void Xtea::encryptValues(uint8_t nrOfValues, uint8_t values[], uint8_t encryptedValues[]) {
  uint8_t tempArray[2];
  if (nrOfValues % 2 != 0) {    
    nrOfValues -= 1;
    encryptedValues[nrOfValues] = values[nrOfValues];
  }
  for (uint8_t i = 0; i < nrOfValues; i += 2) {
    tempArray[0] = values[i];
    tempArray[1] = values[i + 1];
    this->encrypt(tempArray);
    encryptedValues[i] = tempArray[0];
    encryptedValues[i + 1] = tempArray[1];
  }
}

void Xtea::decryptValues(uint8_t nrOfValues, uint8_t values[], uint8_t decryptedValues[]) {
  uint8_t tempArray[2];
  //The Xtea library has to encrypt 2 numbers at once. This is why it cannot encrypt arrays with uneven numbers.
  if (nrOfValues % 2 != 0) {  
Serial.println(nrOfValues);  
    nrOfValues -= 1;
    decryptedValues[nrOfValues] = values[nrOfValues];
  }
  for (uint8_t i = 0; i < nrOfValues; i += 2) {
    tempArray[0] = values[i];
    tempArray[1] = values[i + 1];
    this->decrypt(tempArray);
    decryptedValues[i] = tempArray[0];
    decryptedValues[i + 1] = tempArray[1];
  }
  Serial.print("-----------  ");
  Serial.println(decryptedValues[2]);
}


