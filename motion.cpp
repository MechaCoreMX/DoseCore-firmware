#include "globals.h"
#include "config.h"
#include "motion.h"

bool reedStableLOW(uint8_t pin, uint16_t debounce_ms){
  if (digitalRead(pin) != LOW) return false;
  delay(debounce_ms);
  return (digitalRead(pin) == LOW);
}

bool moveUntilReed(Comp target, uint8_t servoCmd, unsigned long timeout_ms){
  unsigned long t0 = millis();
  servito.write(servoCmd);

  while (millis() - t0 < timeout_ms){
    if (reedStableLOW(compCfg[target].reedPin, REED_DEBOUNCE_MS)){
      servito.write(SERVO_STOP);
      return true;
    }
  }
  servito.write(SERVO_STOP);
  return false;
}

bool moveToComp(Comp target, unsigned long timeout_ms){
  return moveUntilReed(target, compCfg[target].cmdTo, timeout_ms);
}

bool returnHomeFrom(Comp from, unsigned long timeout_ms){
  return moveUntilReed(HOME, compCfg[from].cmdBack, timeout_ms);
}
