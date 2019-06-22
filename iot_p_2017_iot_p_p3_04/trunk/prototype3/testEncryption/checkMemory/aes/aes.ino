#include <AESLib.h>

#define DATA 12345678

uint8_t key[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

void setup() {
  Serial.begin(9600);

  aes128_enc_single(key, DATA);
  aes128_dec_single(key, DATA);
}

void loop() {

}
