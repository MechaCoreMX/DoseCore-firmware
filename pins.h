#include <Arduino.h>

// Servo / Buzzer
static const uint8_t PIN_SERVO  = 6;
static const uint8_t PIN_BUZZER = A3;

// Reeds (INPUT_PULLUP => activo LOW)
static const uint8_t PIN_REED_HOME = 7;
static const uint8_t PIN_REED_A    = 3;
static const uint8_t PIN_REED_B    = 4;
static const uint8_t PIN_REED_C    = 5;

// LCD 16x2 paralelo (LiquidCrystal)
static const uint8_t PIN_LCD_RS = 42;
static const uint8_t PIN_LCD_E  = 44;
static const uint8_t PIN_LCD_D4 = 46;
static const uint8_t PIN_LCD_D5 = 48;
static const uint8_t PIN_LCD_D6 = 50;
static const uint8_t PIN_LCD_D7 = 52;

// Keypad 4x4
static const uint8_t KEYPAD_ROWS = 4;
static const uint8_t KEYPAD_COLS = 4;

static const uint8_t PIN_KEYPAD_ROWS[KEYPAD_ROWS] = {22,24,26,28};
static const uint8_t PIN_KEYPAD_COLS[KEYPAD_COLS] = {30,32,34,36};
