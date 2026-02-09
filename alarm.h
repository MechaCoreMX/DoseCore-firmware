#include <RTClib.h>
#include "types.h"

void beepPattern();
int minuteStamp(const DateTime& now);
void runAlarm(Comp comp, uint8_t doseIdx);
