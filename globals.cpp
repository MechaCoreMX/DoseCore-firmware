#include "pins.h"
#include "config.h"
#include "globals.h"

// Keymap (igual a V2)
static char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

static byte rowPins[KEYPAD_ROWS] = {
  PIN_KEYPAD_ROWS[0], PIN_KEYPAD_ROWS[1], PIN_KEYPAD_ROWS[2], PIN_KEYPAD_ROWS[3]
};
static byte colPins[KEYPAD_COLS] = {
  PIN_KEYPAD_COLS[0], PIN_KEYPAD_COLS[1], PIN_KEYPAD_COLS[2], PIN_KEYPAD_COLS[3]
};

Keypad teclado = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);
LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_E, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);
RTC_DS3231 rtc;
Servo servito;

// CompCfg (igual a V2, incluyendo “camino corto” en C)13
CompCfg compCfg[4] = {
  { PIN_REED_HOME, SERVO_CCW, SERVO_CCW, "HOME" },
  { PIN_REED_A,    SERVO_CW,  SERVO_CCW, "A"    },
  { PIN_REED_B,    SERVO_CW,  SERVO_CCW, "B"    },
  { PIN_REED_C,    SERVO_CCW, SERVO_CW,  "C"    }
};

DoseTime scheduleTbl[4][3];

// Anti re-disparo
int lastTriggeredKey = -1;
int lastTriggeredMinuteStamp = -1;
