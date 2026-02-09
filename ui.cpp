#include "globals.h"
#include "config.h"
#include "motion.h"
#include "ui.h"

void showDateTime(const DateTime& now){
  lcd.setCursor(0,0);
  lcd.print(now.day()); lcd.print("/");
  lcd.print(now.month()); lcd.print("/");
  lcd.print(now.year());

  lcd.setCursor(0,1);
  if (now.hour()<10) lcd.print("0");
  lcd.print(now.hour()); lcd.print(":");
  if (now.minute()<10) lcd.print("0");
  lcd.print(now.minute()); lcd.print(":");
  if (now.second()<10) lcd.print("0");
  lcd.print(now.second());
}

bool read2Digits(uint8_t &value){
  char a = teclado.waitForKey();
  char b = teclado.waitForKey();
  if (a<'0'||a>'9'||b<'0'||b>'9') return false;
  value = (a-'0')*10 + (b-'0');
  return true;
}

void configOneDose(){
  lcd.clear();
  lcd.print("Comp 1=A 2=B 3=C");
  char kc = teclado.waitForKey();
  Comp comp = (kc=='1')?A:(kc=='2')?B:(kc=='3')?C:HOME;
  if (comp==HOME) { lcd.clear(); return; }

  lcd.clear();
  lcd.print("Dosis 1/2/3?");
  char kd = teclado.waitForKey();
  uint8_t d = (kd=='1')?0:(kd=='2')?1:(kd=='3')?2:255;
  if (d==255) { lcd.clear(); return; }

  lcd.clear();
  lcd.print("Hora (HH):");
  lcd.setCursor(0,1);
  uint8_t hh=0, mm=0;
  if(!read2Digits(hh) || hh>23) { lcd.clear(); lcd.print("HH invalida"); delay(900); lcd.clear(); return; }

  lcd.clear();
  lcd.print("Min (MM):");
  lcd.setCursor(0,1);
  if(!read2Digits(mm) || mm>59) { lcd.clear(); lcd.print("MM invalido"); delay(900); lcd.clear(); return; }

  scheduleTbl[comp][d].hour = hh;
  scheduleTbl[comp][d].minute = mm;
  scheduleTbl[comp][d].enabled = true;

  lcd.clear();
  lcd.print("Guardado ");
  lcd.print(compCfg[comp].name);
  lcd.print(" D"); lcd.print(d+1);
  delay(900);
  lcd.clear();
}

void manualOpen(Comp comp){
  lcd.clear();
  lcd.print("Manual -> ");
  lcd.print(compCfg[comp].name);

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

  lcd.setCursor(0,1);
  lcd.print("6=HOME");

  while (true){
    char k = teclado.getKey();
    if (k == KEY_ACK) break;
    delay(50);
  }

  returnHomeFrom(comp, MOVE_TIMEOUT_MS);
  lcd.clear();
}
