

#include "CircularBuffer.h"

void printStats(CircularBuffer* buffer, char* title, bool printSet){
  
  Serial.println(title);
  Serial.println(("==========="));
  Serial.print(("Stdev: "));
  Serial.println(calcStDev(buffer));
  Serial.print(("Average: "));
  Serial.println(calcAvg(buffer));
  uint32_t min;
  uint32_t max;
  getMinMax(buffer, min, max);
  Serial.print(("Max: "));
  Serial.println(max);
  Serial.print(("Min: "));
  Serial.println(min);

  if (printSet){
    printBuffer(buffer);
  }
  Serial.println(("==========="));
}

float calcStDev(CircularBuffer* buffer){
  uint32_t tempStart = buffer->start;
  uint32_t tempCount = buffer->count;

  uint64_t sum = 0;
  uint64_t squared = 0;

  while (isAvailable(buffer)){
      uint32_t value = readValue(buffer);
      squared += value * value;
      sum += value;
  }
  buffer->start = tempStart;
  buffer->count = tempCount;


  float stdevsquared = ( squared - (float(sum*sum)/tempCount))/(tempCount - 1);

  float stdev = pow(stdevsquared, 0.5);
  return stdev;
}

float calcAvg(CircularBuffer* buffer){
  uint32_t tempStart = buffer->start;
  uint32_t tempCount = buffer->count;
  uint64_t sum = 0;

  while (isAvailable(buffer)){
      sum +=  readValue(buffer);
  }
  buffer->count = tempCount;
  buffer->start = tempStart;

  return (float)sum / tempCount;
}

void getMinMax(CircularBuffer* buffer, uint32_t& min, uint32_t& max){
  uint32_t tempStart = buffer->start;
  uint32_t tempCount = buffer->count;

  uint32_t val = readValue(buffer);
  min = val;
  max = val;

  while (isAvailable(buffer)){
      val =  readValue(buffer);
      if (val < min){
        min = val;
      }
      if (val > max){
        max = val;
      }
  }
  buffer->count = tempCount;
  buffer->start = tempStart;

}

void printBuffer(CircularBuffer* buffer){
  uint32_t tempStart = buffer->start;
  uint32_t tempCount = buffer->count;

  Serial.println(("------------\nValues"));
  while (isAvailable(buffer)){
    Serial.println(readValue(buffer));
  }
  Serial.println(("------------"));
  buffer->count = tempCount;
  buffer->start = tempStart;

}
