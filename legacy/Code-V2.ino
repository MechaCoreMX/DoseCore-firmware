/*
  Pastillero Automatizado - Firmware V2 (Minimalista + Manual)
  Plataforma: Arduino Mega 2560

  Teclas:
   - A = Abrir manual compartimento A (queda esperando 6 para regresar HOME)
   - B = Abrir manual compartimento B (queda esperando 6 para regresar HOME)
   - C = Abrir manual compartimento C (queda esperando 6 para regresar HOME)
   - D = Configurar 1 dosis (elige comp 1/2/3, dosis 1/2/3, HH, MM)
   - 6 = ACK (para silenciar alarma y regresar a HOME / o regresar en manual)

  Hardware:
   - RTC DS3231 (RTClib)
   - LCD 16x2 paralelo (LiquidCrystal pins: 42,44,46,48,50,52)
   - Keypad 4x4 (filas: 22,24,26,28 / columnas: 30,32,34,36)
   - Servo rotación continua en pin 6 (comandos 69/90/99)
   - Buzzer pasivo en A3
   - Reed switches (INPUT_PULLUP, activo LOW):
        HOME: pin 7
        A:    pin 3
        B:    pin 4
        C:    pin 5

  Movimiento (deducido del firmware original):
   - A: ir 99, volver 69
   - B: ir 99, volver 69
   - C: ir 69, volver 99  (camino corto)
*/

#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

// ===================== Hardware mapping =====================
static const uint8_t PIN_SERVO   = 6;
static const uint8_t PIN_BUZZER  = A3;

// Reeds (INPUT_PULLUP => activo LOW)
static const uint8_t PIN_REED_HOME = 7;
static const uint8_t PIN_REED_A    = 3;
static const uint8_t PIN_REED_B    = 4;
static const uint8_t PIN_REED_C    = 5;

// Servo commands for continuous rotation
static const uint8_t SERVO_STOP = 90;
static const uint8_t SERVO_CW   = 99;
static const uint8_t SERVO_CCW  = 72;

// "ACK" key (silenciar / regresar HOME)
static const char KEY_ACK = '6';

// ===================== Keypad & LCD =====================
const byte FILAS = 4, COLUMNAS = 4;
char keys[FILAS][COLUMNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte pinesFilas[FILAS]       = {22,24,26,28};
byte pinesColumnas[COLUMNAS] = {30,32,34,36};

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);
LiquidCrystal lcd(42,44,46,48,50,52);
RTC_DS3231 rtc;
Servo servito;

// ===================== Data structures =====================
enum Comp : uint8_t { HOME=0, A=1, B=2, C=3 };

struct CompCfg {
  uint8_t reedPin;
  uint8_t cmdTo;     // comando servo para ir a ese compartimento
  uint8_t cmdBack;   // comando servo para volver a HOME desde ese compartimento
  const char* name;  // etiqueta
};

CompCfg compCfg[] = {
  { PIN_REED_HOME, SERVO_CCW, SERVO_CCW, "HOME" }, // HOME
  { PIN_REED_A,    SERVO_CW,  SERVO_CCW, "A"    },
  { PIN_REED_B,    SERVO_CW,  SERVO_CCW, "B"    },
  { PIN_REED_C,    SERVO_CCW, SERVO_CW,  "C"    }  // invertido para camino corto
};

struct DoseTime {
  uint8_t hour;
  uint8_t minute;
  bool enabled;
};

// scheduleTbl[comp][dose]  comp: A,B,C => 1..3 ; dose: 0..2
DoseTime scheduleTbl[4][3]; // index 0(HOME) no se usa

// Anti re-disparo en el mismo minuto
int lastTriggeredKey = -1;          // key = comp*10 + dose
int lastTriggeredMinuteStamp = -1;  // stamp por minuto

// ===================== Helpers =====================
bool reedStableLOW(uint8_t pin, uint16_t debounce_ms=25){
  if (digitalRead(pin) != LOW) return false;
  delay(debounce_ms);
  return (digitalRead(pin) == LOW);
}

bool moveUntilReed(Comp target, uint8_t servoCmd, unsigned long timeout_ms=5000){
  unsigned long t0 = millis();
  servito.write(servoCmd);

  while (millis() - t0 < timeout_ms){
    if (reedStableLOW(compCfg[target].reedPin, 25)){
      servito.write(SERVO_STOP);
      return true;
    }
  }
  servito.write(SERVO_STOP);
  return false;
}

bool moveToComp(Comp target, unsigned long timeout_ms=5000){
  return moveUntilReed(target, compCfg[target].cmdTo, timeout_ms);
}

bool returnHomeFrom(Comp from, unsigned long timeout_ms=5000){
  return moveUntilReed(HOME, compCfg[from].cmdBack, timeout_ms);
}

void beepPattern(){
  tone(PIN_BUZZER, 880, 120);
  delay(180);
  noTone(PIN_BUZZER);
}

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

int minuteStamp(const DateTime& now){
  return now.day()*24*60 + now.hour()*60 + now.minute();
}

// ===================== Manual open =====================
void manualOpen(Comp comp){
  lcd.clear();
  lcd.print("Manual -> ");
  lcd.print(compCfg[comp].name);

  bool okGo = moveToComp(comp, 6000);
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

  // Espera ACK para regresar
  while (true){
    char k = teclado.getKey();
    if (k == KEY_ACK) break;
    delay(50);
  }

  returnHomeFrom(comp, 6000);
  lcd.clear();
}

// ===================== Alarm handling =====================
void runAlarm(Comp comp, uint8_t doseIdx){
  lcd.clear();
  lcd.print("Alarma ");
  lcd.print(compCfg[comp].name);
  lcd.print(" D");
  lcd.print(doseIdx+1);
  lcd.setCursor(0,1);
  lcd.print("ACK ");
  lcd.print(KEY_ACK);

  bool okGo = moveToComp(comp, 6000);
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

  bool okBack = returnHomeFrom(comp, 6000);
  if (!okBack){
    lcd.clear();
    lcd.print("Error: no HOME");
    delay(1200);
  }

  lcd.clear();
}

// ===================== Minimal UI: set one schedule =====================
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

// ===================== Setup & loop =====================
void setup(){
  Wire.begin();

  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Pastillero V2");
  delay(800);
  lcd.clear();

  if (!rtc.begin()){
    lcd.print("RTC FAIL");
    while(1);
  }
  // Ajuste RTC (solo 1 vez si lo necesitas):
  // rtc.adjust(DateTime(__DATE__, __TIME__));

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
  lcd.print("Buscando HOME...");
  bool okHome = moveUntilReed(HOME, SERVO_CCW, 7000);
  lcd.clear();
  lcd.print(okHome ? "HOME OK" : "HOME FAIL");
  delay(800);
  lcd.clear();
}

void loop(){
  DateTime now = rtc.now();
  showDateTime(now);

  // Teclas manuales + config:
  // A/B/C -> abrir manual A/B/C
  // D     -> configurar una dosis
  char k = teclado.getKey();
  if (k == 'A'){
    manualOpen(A);
  } else if (k == 'B'){
    manualOpen(B);
  } else if (k == 'C'){
    manualOpen(C);
  } else if (k == 'D'){
    configOneDose();
  }

  // Revisar alarmas
  int ms = minuteStamp(now);

  for (uint8_t comp = A; comp <= C; comp++){
    for (uint8_t d=0; d<3; d++){
      if (!scheduleTbl[comp][d].enabled) continue;

      if (now.hour() == scheduleTbl[comp][d].hour && now.minute() == scheduleTbl[comp][d].minute){
        int key = comp*10 + d;
        if (!(lastTriggeredMinuteStamp == ms && lastTriggeredKey == key)){
          lastTriggeredMinuteStamp = ms;
          lastTriggeredKey = key;
          runAlarm((Comp)comp, d);
        }
      }
    }
  }

  delay(150);
}
