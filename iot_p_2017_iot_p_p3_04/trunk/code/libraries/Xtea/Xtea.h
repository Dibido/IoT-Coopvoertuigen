/*
  Xtea.h - Crypto library
  Written by Frank Kienast in November, 2010
  From: https://github.com/franksmicro/Arduino/tree/master/libraries/Xtea
*/
#ifndef Xtea_h
#define Xtea_h

#include <Arduino.h>

/*
 * @brief This class can encrypt and decrypt two numbers with eachother
 */
class Xtea
{
  public:
    Xtea(uint32_t key[4]);
    
    /*
     * @param data[2] data that has to be encrypted
     */
    void encrypt(uint8_t data[2]);
    
    /*
     * @param data[2] data that has to be encrypted
     */
    void decrypt(uint8_t data[2]);
	
	/*
	* @param xtea The xtea instance for the encryption.
	*/
	void encryptValues(uint8_t nrOfValues, uint8_t values[], uint8_t encryptedValues[]);

	void decryptValues(uint8_t nrOfValues, uint8_t values[], uint8_t decryptedValues[]);

  private:
    /*
     * This is the key
     */
    uint32_t _key[4];
};

#endif

