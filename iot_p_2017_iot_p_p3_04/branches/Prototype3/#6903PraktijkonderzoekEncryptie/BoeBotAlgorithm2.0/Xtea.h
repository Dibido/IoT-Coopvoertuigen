/*
  Xtea.h - Crypto library
  Written by Frank Kienast in November, 2010
*/
#ifndef Xtea_h
#define Xtea_h

#include <Arduino.h>

class Xtea
{
  public:
    Xtea(unsigned long key[4]);
    void encrypt(unsigned long data[2]);
    void decrypt(unsigned long data[2]);
  private:
    unsigned long _key[4];
};

#endif

