#define BUFFERSIZE 200
#define TIMES 200

// https://github.com/DavyLandman/AESLib commit: cc4f8ae5e12fa2d5c41b9c86a7ae36655256b6d2
#include <AESLib.h>
#include "CircularBuffer.h"


void encryptTest(uint32_t n, char data[]){

  CircularBuffer buffer;
  uint8_t key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

  startBuffer(&buffer);

  uint32_t _start;
  uint32_t _end;

  Serial.println(F("AES 128 bit block size 128bit key"));

  for (uint32_t i = 0; i < n; ++i){
        _start = micros();
          aes128_enc_single(key, data);
        _end = micros();
        addValue(&buffer, _end-_start);
  }
    Serial.println(F("Encrypt (microseconds)"));
    printStats(&buffer, true);

  for (uint32_t i = 0; i < n; ++i){
      _start = micros();
      aes128_dec_single(key, data);
      _end = micros();
      addValue(&buffer, _end-_start);
  }


    Serial.println(F("Decrypt (microseconds)"));
    printStats(&buffer,true);

}

void setup(){
  Serial.begin(9600);

  Serial.print(("N = "));
  Serial.println(TIMES);
    encryptTest(TIMES, "12345678");

}

void loop(){

}
