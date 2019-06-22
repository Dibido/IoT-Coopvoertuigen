
#ifndef BUFFER_H_
#define BUFFER_H_

#include "Arduino.h"

#ifndef BUFFERSIZE
  #define BUFFERSIZE 100
#endif
typedef struct {
  uint32_t start;
  uint32_t count;
  uint16_t buffer[BUFFERSIZE];
} CircularBuffer;

void startBuffer(CircularBuffer* buffer);

bool addValue(CircularBuffer *buffer, uint32_t value);

uint32_t readValue(CircularBuffer *buffer);

bool isAvailable(CircularBuffer *buffer);

#endif
