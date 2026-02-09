#include <Arduino.h>

// Servo commands (rotación continua)
static const uint8_t SERVO_STOP = 90;
static const uint8_t SERVO_CW   = 99;
static const uint8_t SERVO_CCW  = 72;

// Tecla ACK (silenciar / regresar HOME)
static const char KEY_ACK = '6';

// Timing / seguridad
static const uint16_t REED_DEBOUNCE_MS    = 25;
static const uint16_t LOOP_DELAY_MS       = 150;
static const uint32_t MOVE_TIMEOUT_MS     = 6000;
static const uint32_t HOME_TIMEOUT_MS     = 7000;

// LCD
static const uint8_t LCD_COLS = 16;
static const uint8_t LCD_ROWS = 2;
