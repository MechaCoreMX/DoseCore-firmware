#include <Wire.h>
#include "pins.h"
#include "config.h"
#include "globals.h"
#include "motion.h"
#include "ui.h"
#include "alarm.h"

void setup(){
  Wire.begin();

  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.clear();
  lcd.print("Pastillero V2");
  delay(800);
  lcd.clear();

  if (!rtc.begin()){
    lcd.print("RTC FAIL");
    while(1);
  }
  // rtc.adjust(DateTime(__DATE__, __TIME__)); // solo 1 vez si lo necesitas

  pinMode(PIN_BUZZER, OUTPUT);

  pinMode(PIN_REED_HOME, INPUT_PULLUP);
  pinMode(PIN_REED_A,    INPUT_PULLUP);
  pinMode(PIN_REED_B,    INPUT_PULLUP);
  pinMode(PIN_REED_C,    INPUT_PULLUP);

  servito.attach(PIN_SERVO);
  servito.write(SERVO_STOP);

  // Inicializa horarios deshabilitados
  for (int c=0;c<4;c++){
    for (int d=0;d<3;d++){
      scheduleTbl[c][d].hour = 0;
      scheduleTbl[c][d].minute = 0;
      scheduleTbl[c][d].enabled = false;
    }
  }

  // Homing automático
  lcd.print("Buscando HOME.");
  bool okHome = moveUntilReed(HOME, SERVO_CCW, HOME_TIMEOUT_MS);
  lcd.clear();
  lcd.print(okHome ? "HOME OK" : "HOME FAIL");
  delay(800);
  lcd.clear();
}

void loop(){
  DateTime now = rtc.now();
  showDateTime(now);

  // Teclas: A/B/C manual, D configurar 1 dosis
  char k = teclado.getKey();
  if (k == 'A')      manualOpen(A);
  else if (k == 'B') manualOpen(B);
  else if (k == 'C') manualOpen(C);
  else if (k == 'D') configOneDose();

  // Revisar alarmas (anti re-disparo)
  int ms = minuteStamp(now);

  for (uint8_t comp = A; comp <= C; comp++){
    for (uint8_t d=0; d<3; d++){
      if (!scheduleTbl[comp][d].enabled) continue;

      if (now.hour() == scheduleTbl[comp][d].hour &&
          now.minute() == scheduleTbl[comp][d].minute){

        int key = comp*10 + d;
        if (!(lastTriggeredMinuteStamp == ms && lastTriggeredKey == key)){
          lastTriggeredMinuteStamp = ms;
          lastTriggeredKey = key;
          runAlarm((Comp)comp, d);
        }
      }
    }
  }

  delay(LOOP_DELAY_MS);
}
