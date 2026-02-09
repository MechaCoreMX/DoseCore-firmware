#include "globals.h"
#include "config.h"
#include "motion.h"
#include "alarm.h"

void beepPattern(){
  tone(PIN_BUZZER, 880, 120);
  delay(180);
  noTone(PIN_BUZZER);
}

int minuteStamp(const DateTime& now){
  return now.day()*24*60 + now.hour()*60 + now.minute();
}

void runAlarm(Comp comp, uint8_t doseIdx){
  lcd.clear();
  lcd.print("Alarma ");
  lcd.print(compCfg[comp].name);
  lcd.print(" D");
  lcd.print(doseIdx+1);
  lcd.setCursor(0,1);
  lcd.print("ACK ");
  lcd.print(KEY_ACK);

  bool okGo = moveToComp(comp, MOVE_TIMEOUT_MS);
  if (!okGo){
    lcd.clear();
    lcd.print("Error: no llega");
    lcd.setCursor(0,1);
    lcd.print("a comp ");
    lcd.print(compCfg[comp].name);
    delay(1200);
    lcd.clear();
    return;
  }

  while (true){
    beepPattern();
    char k = teclado.getKey();
    if (k == KEY_ACK) break;
  }

  bool okBack = returnHomeFrom(comp, MOVE_TIMEOUT_MS);
  if (!okBack){
    lcd.clear();
    lcd.print("Error: no HOME");
    delay(1200);
  }

  lcd.clear();
}
