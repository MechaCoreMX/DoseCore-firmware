#include <Arduino.h>

enum Comp : uint8_t { HOME=0, A=1, B=2, C=3 };

struct CompCfg {
  uint8_t reedPin;
  uint8_t cmdTo;
  uint8_t cmdBack;
  const char* name;
};

struct DoseTime {
  uint8_t hour;
  uint8_t minute;
  bool enabled;
};
