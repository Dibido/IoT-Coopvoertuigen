#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>

#ifdef DEBUG_MODE
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

#endif /* DEBUG_H */