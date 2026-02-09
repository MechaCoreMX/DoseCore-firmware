#include <RTClib.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

#include "types.h"

// Objetos HW
extern RTC_DS3231 rtc;
extern LiquidCrystal lcd;
extern Keypad teclado;
extern Servo servito;

// Configuración de compartimentos y horarios
extern CompCfg compCfg[4];
extern DoseTime scheduleTbl[4][3];

// Anti re-disparo
extern int lastTriggeredKey;
extern int lastTriggeredMinuteStamp;
