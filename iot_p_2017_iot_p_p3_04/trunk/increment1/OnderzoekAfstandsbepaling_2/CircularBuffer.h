
#ifndef BUFFER_H_
#define BUFFER_H_

#include "Arduino.h"

#ifndef BUFFERSIZE
  #define BUFFERSIZE 100
#endif
typedef struct {
  uint32_t start;
  uint32_t count;
  float buffer[BUFFERSIZE];
} CircularBuffer;

void startBuffer(CircularBuffer* buffer);

bool addValue(CircularBuffer *buffer, float value);

float readValue(CircularBuffer *buffer);

bool isAvailable(CircularBuffer *buffer);

#endif
