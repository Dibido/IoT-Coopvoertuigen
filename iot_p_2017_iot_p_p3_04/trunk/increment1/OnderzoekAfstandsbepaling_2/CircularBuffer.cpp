
#include "CircularBuffer.h"
#include <stdio.h>

void startBuffer(CircularBuffer* buffer){
  buffer->start = 0;
  buffer->count = 0;
}

bool addValue(CircularBuffer *buffer, float value) {
    buffer->buffer[(buffer->start + buffer->count) % BUFFERSIZE] = value;
    ++buffer->count;
    return true;
}

float readValue(CircularBuffer *buffer) {
  if (isAvailable(buffer)) {
    uint32_t returnval = buffer->buffer[buffer->start];
    ++buffer->start;
    --buffer->count;
    buffer->start %= BUFFERSIZE;
    return returnval;
  } else {
    return -1;
  }
}

bool isAvailable(CircularBuffer *buffer){
  return buffer->count > 0;
}
