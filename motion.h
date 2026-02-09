#include <Arduino.h>
#include "types.h"

bool reedStableLOW(uint8_t pin, uint16_t debounce_ms = 25);
bool moveUntilReed(Comp target, uint8_t servoCmd, unsigned long timeout_ms = 5000);
bool moveToComp(Comp target, unsigned long timeout_ms = 5000);
bool returnHomeFrom(Comp from, unsigned long timeout_ms = 5000);
