#include <Wire.h>   
#include <RTClib.h>   
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h> 
//#include <SFE_BMP180.h>

//////OBJETOS DEL PROGRAMA//////
Servo servito; 
//SFE_BMP180 bmp180;

///NOTAS MUSICALES PARA BUZZER
#define NOTE_B0  31  // notas y frecuencias
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define BUZZER_PASIVO A3    // buzzer pasivo en pin A3

int melodia[] = {    // array con las notas de la melodia
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int duraciones[] = {    // array con la duracion de cada nota
  4, 8, 8, 4, 4, 4, 4, 4
};

///TECLADO
const byte FILAS = 4;     // define numero de filas
const byte COLUMNAS = 4;    // define numero de columnas
char keys[FILAS][COLUMNAS] = {    // define la distribucion de teclas
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};


byte pinesFilas[FILAS] = {22,24,26,28};   // pines correspondientes a las filas
byte pinesColumnas[COLUMNAS] = {30,32,34,36}; // pines correspondientes a las columnas

///Compartimientos
char h1[2] = {'-','-'};
char h2[2] = {'-','-'};
char h3[2] = {'-','-'};
char h4[2] = {'-','-'};
char h5[2] = {'-','-'};
char h6[2] = {'-','-'};
char h7[2] = {'-','-'};
char h8[2] = {'-','-'};
char h9[2] = {'-','-'};
char s1[2] = {'-','-'};
char s2[2] = {'-','-'}; 
char s3[2] = {'-','-'}; 
char s4[2] = {'-','-'}; 
char s5[2] = {'-','-'}; 
char s6[2] = {'-','-'}; 
char s7[2] = {'-','-'};
char s8[2] = {'-','-'};  
char s9[2] = {'-','-'};  


/////OBJETOS DEL PROGRAMA/////
Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS); 
LiquidCrystal lcd(42,44,46,48,50,52);
RTC_DS3231 rtc;     // crea objeto del tipo RTC_DS3231

///Funciones///
void rtc_inicializacion(void);
void lcd_inicializacion(void);
void alarma_C1D1(DateTime, int, int, String);
void alarma_C2D1(DateTime, int, int, String);
void alarma_C3D1(DateTime, int, int, String);
void rellenar_compartimiento_A(void);
void rellenar_compartimiento_B(void);
void rellenar_compartimiento_C(void);
void temp(void);

int inicializacion = 0;

void setup () {
 rtc_inicializacion();
 lcd_inicializacion();
// Serial.begin(9600);
 servito.attach(6); 
 servito.write(90);
 pinMode(BUZZER_PASIVO, OUTPUT); // pin A1
 pinMode (7, INPUT_PULLUP); ///TAPON
 pinMode (3, INPUT_PULLUP); ///A
 pinMode (4, INPUT_PULLUP); ///B
 pinMode (5, INPUT_PULLUP); ///C

 while(inicializacion != 5){
  servito.write(69);
  if(digitalRead(7) == LOW){
  servito.write(90);
  inicializacion = 5; 
  }
 }
 
 //if(!bmp180.begin()){
 // while(1);
 //}
 
}

char tecla, teclita, teclita_2, teclita_3;

///Banderas de estado de cada Compartimiento
String banderita = "M";
String banderita_1 = "M";
String banderita_2 = "M";
String banderita_3 = "M";
String banderita_4 = "M";
String banderita_5 = "M";
String banderita_6 = "M";
String banderita_7 = "M";
String banderita_8 = "M";

///Bandera de estado del sistema
bool bandera = false;

///Variables utilizada para Reloj
///Compartimineto #1
int segundos,horas; ///Primera dosis 
int minutosc1d2,horasc1d2; ///Segunda dosis
int minutosc1d3,horasc1d3; ///Tercera dosis

///Compartimiento #2
int minutosc2d1,horasc2d1; ///Primera dosis 
int minutosc2d2,horasc2d2; ///Segunda dosis
int minutosc2d3,horasc2d3;  ///Tercera dosis

///Compartimiento #3
int minutosc3d1,horasc3d1; ///Primera dosis 
int minutosc3d2,horasc3d2; ///Segunda dosis
int minutosc3d3,horasc3d3; ///Tercera dosis

///Rompeciclos
 ///Alarma C1D#N

//char status; 
void loop () { 
   
 DateTime fecha = rtc.now();        // funcion que devuelve fecha y horario en formato DateTime y asigna a variable fecha
 lcd.setCursor(0,0);     
 lcd.print(fecha.day());   
 lcd.print("/");         
 lcd.print(fecha.month());  
 lcd.print("/");       
 lcd.print(fecha.year());   
 lcd.print(" ");   
 lcd.setCursor(0,1);        
 lcd.print(fecha.hour());       
 lcd.print(":");         
 lcd.print(fecha.minute());       
 lcd.print(":");        
 lcd.print(fecha.second());  
 lcd.print(" 1) 2) 3)"); 

 ///temp();

if (tecla = teclado.getKey()){
lcd.clear();
while(bandera==false){
 switch(tecla){
 case '1':                           //COMPARTIMIENTO NO.1
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Comparti. (A) ");
  lcd.setCursor(0,1);
  lcd.print("Dosis 1) 2) 3)");
  lcd.setCursor(10,1); 
  while(bandera == false){
  teclita = teclado.waitForKey();
  switch (teclita){                  //Seleccion de dosis (Diferentes Alarmas)
  case '1':
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Confi. Dosis 1");
  lcd.setCursor(0,1); lcd.print("Minutos:");
  lcd.setCursor(10,1); 
  lcd.print(s1[0]); 
  lcd.print(s1[1]);
  for(int i=0; i < 2; i++){
  s1[i] = teclado.waitForKey();
  lcd.setCursor(10,1); 
  lcd.print(s1[0]); 
  lcd.print(s1[1]);
  segundos = atof(s1);
  if(segundos > 60){
  i=-1;  
  s1[0] = '-'; s1[1] = '-';
  lcd.setCursor(10,1);
  lcd.print(s1[0]);
  lcd.print(s1[1]);
  }
  }
  lcd.clear(); 
  s1[0] = ' ';  s1[1] = ' ';   ///EVITA COCATENACION DE LOS DATOS
  /////Configuracion de horas////////
  lcd.setCursor(1,0);
  lcd.print("Confi. Dosis 1");
  lcd.setCursor(0,1); lcd.print("Horas:");
  for(int i=0; i < 2; i++){
  lcd.setCursor(10,1); 
  lcd.print(h1[0]); 
  lcd.print(h1[1]);
  h1[i] = teclado.waitForKey();
  horas = atof(h1);
  if(horas > 24){
  i=-1;   
  h1[0] = '-'; h1[1] = '-';
  lcd.setCursor(10,1); 
  lcd.print(h1[0]); 
  lcd.print(h1[1]);
  }
  } 
  banderita = "A";
  lcd.clear();  
  h1[0] = '-'; h1[1] = '-';
  s1[0] = '-'; s1[1] = '-';
  break;
  case '2': 
  lcd.clear(); 
  lcd.setCursor(1,0);
  lcd.print("Confi. Dosis 2");
  lcd.setCursor(0,1); lcd.print("Minutos:");
  lcd.setCursor(10,1); 
  lcd.print(s2[0]); 
  lcd.print(s2[1]);
  for(int j=0; j < 2; j++){
  s2[j] = teclado.waitForKey();
  lcd.setCursor(10,1); 
  lcd.print(s2[0]); 
  lcd.print(s2[1]);
  minutosc1d2 = atof(s2);
  if(minutosc1d2 > 60){
  j=-1;  
  s2[0] = '-'; s2[1] = '-';
  Serial.print(minutosc1d2);
  lcd.setCursor(10,1);
  lcd.print(s2[0]); 
  lcd.print(s2[1]);
  }
  }
  lcd.clear(); 
  s2[0] = ' '; s2[1] = ' ';   ///EVITA COCATENACION DE LOS DATOS
  /////Configuracion de horas////////
  lcd.setCursor(1,0);
  lcd.print("Confi. Dosis 2");
  lcd.setCursor(0,1); lcd.print("Horas:");
  for(int j=0; j < 2; j++){
  lcd.setCursor(10,1); 
  lcd.print(h2[0]); 
  lcd.print(h2[1]);
  h2[j] = teclado.waitForKey();
  horasc1d2 = atof(h2);
  if(horasc1d2 > 24){
  j=-1;   
  h2[0] = '-'; h2[1] = '-';
  lcd.setCursor(10,1); 
  lcd.print(h2[0]); 
  lcd.print(h2[1]);
  }
  }
  banderita_1 = 'B';
  lcd.clear();
  h2[0] = '-'; h2[1] = '-';
  s2[0] = '-'; s2[1] = '-';
  break;
  case '3': 
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Confi. Dosis 3");
  lcd.setCursor(0,1); lcd.print("Minutos:");
  lcd.setCursor(10,1); 
  lcd.print(s3[0]); 
  lcd.print(s3[1]);
  for(int i=0; i < 2; i++){
  s3[i] = teclado.waitForKey();
  lcd.setCursor(10,1); 
  lcd.print(s3[0]); 
  lcd.print(s3[1]);
  minutosc1d3 = atof(s3);
  if(minutosc1d3 > 60){
  i=-1;  
  s3[0] = '-'; s3[1] = '-';
  lcd.setCursor(10,1);
  lcd.print(s3);
  }
  }
  
  lcd.clear(); s3[0] = ' '; s3[1] = ' ';   ///EVITA COCATENACION DE LOS DATOS
 
  /////Configuracion de horas////////
  lcd.setCursor(1,0);
  lcd.print("Confi. Dosis 3");
  lcd.setCursor(0,1); lcd.print("Horas:");
  for(int i=0; i < 2; i++){
  lcd.setCursor(10,1); 
  lcd.print(h3[0]); 
  lcd.print(h3[1]);
  h3[i] = teclado.waitForKey();
  horasc1d3 = atof(h3);
  if(horas > 24){
  i=-1;   
  h3[0] = '-'; h3[1] = '-';
  lcd.setCursor(10,1);
  lcd.print(h3[0]); 
  lcd.print(h3[1]);
  }
  }
  banderita_2 = "C";
  lcd.clear();
  h3[0] = '-'; h3[1] = '-';
  s3[0] = '-'; s3[1] = '-';
  break;
  default:
  banderita = "M";
  banderita_1="M";
  banderita_2="M"; 
  break; 
  }
  lcd.clear();
  bandera = true;
  }
  break;
  case '2':                         ////COMPARTIMIENTO NO.2
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Comparti. (B) ");
  lcd.setCursor(0,1);
  lcd.print("Dosis 1) 2) 3)");
  lcd.setCursor(10,1); 
  while(bandera == false){
  teclita_2 = teclado.waitForKey();
  switch (teclita_2){                 
  case '1':
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Confi. Dosis 1");
  lcd.setCursor(0,1); lcd.print("Minutos:");
  lcd.setCursor(10,1); 
  lcd.print(s4[0]); lcd.print(s4[1]);
  for(int i=0; i < 2; i++){
  s4[i] = teclado.waitForKey();
  lcd.setCursor(10,1); 
  lcd.print(s4[0]); lcd.print(s4[1]);
  minutosc2d1 = atof(s4);
  if(minutosc2d1 > 60){
  i=-1;  
  s4[0] = '-'; s4[1] = '-';
  lcd.setCursor(10,1);
  lcd.print(s4[0]); lcd.print(s4[1]);
  }
  }
  lcd.clear(); 
  s4[0] = ' '; s4[1] = ' ';   ///EVITA COCATENACION DE LOS DATOS
 
  /////Configuracion de horas////////
  lcd.setCursor(1,0);
  lcd.print("Confi. Dosis 1");
  lcd.setCursor(0,1); lcd.print("Horas:");
  for(int i=0; i < 2; i++){
  lcd.setCursor(10,1); 
  lcd.print(h4[0]); lcd.print(h4[1]);
  h4[i] = teclado.waitForKey();
  horasc2d1 = atof(h4);
  if(horasc2d1 > 24){
  i=-1;   
  h4[0] = '-'; h4[1] = '-';
  lcd.setCursor(10,1); lcd.print(h4[0]); lcd.print(h4[1]);
  }
  }
  banderita_3 = "D";
  lcd.clear();
  h4[0] = '-'; h4[1] = '-';
  s4[0] = '-'; s4[1] = '-';
  break;
  case '2': 
  lcd.clear(); 
  lcd.setCursor(1,0);
  lcd.print("Confi. Dosis 2");
  lcd.setCursor(0,1); lcd.print("Minutos:");
  lcd.setCursor(10,1); 
  lcd.print(s5[0]); lcd.print(s5[1]);
  for(int i=0; i < 2; i++){
  s5[i] = teclado.waitForKey();
  lcd.setCursor(10,1); 
  lcd.print(s5[0]); lcd.print(s5[1]);
  minutosc2d2 = atof(s5);
  if(minutosc2d2 > 60){
  i=-1;  
  s5[0] = '-'; s5[1] = '-';
  lcd.setCursor(10,1);
  lcd.print(s5[0]); lcd.print(s5[1]);
  }
  }
  lcd.clear(); 
  s5[0] = ' '; s5[1] = ' ';   ///EVITA COCATENACION DE LOS DATOS
  /////Configuracion de horas////////
  lcd.setCursor(1,0);
  lcd.print("Confi. Dosis 2");
  lcd.setCursor(0,1); lcd.print("Horas:");
  for(int i=0; i < 2; i++){
  lcd.setCursor(10,1); 
  lcd.print(h5[0]); lcd.print(h5[1]);
  h5[i] = teclado.waitForKey();
  horasc2d2 = atof(h5);
  if(horasc2d2 > 24){
  i=-1;   
  h5[0] = '-'; h5[1] = '-';
  lcd.setCursor(10,1); lcd.print(h5[0]); lcd.print(h5[1]);
  }
  }
  banderita_4 = "E";
  h5[0] = '-'; h5[1] = '-';
  s5[0] = '-'; s5[1] = '-';
  break;
  case '3': 
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Confi. Dosis 3");
  lcd.setCursor(0,1); lcd.print("Minutos:");
  lcd.setCursor(10,1); 
  lcd.print(s6[0]); lcd.print(s6[1]);
  for(int i=0; i < 2; i++){
  s6[i] = teclado.waitForKey();
  lcd.setCursor(10,1); 
  lcd.print(s6[0]); lcd.print(s6[1]);
  minutosc2d3 = atof(s6);
  if(minutosc2d3 > 60){
  i=-1;  
  s6[0] = '-'; s6[1] = '-';
  lcd.setCursor(10,1);
  lcd.print(s6[0]); lcd.print(s6[1]);
  }
  }
  lcd.clear(); s6[0] = ' '; s6[1] = ' ';   ///EVITA COCATENACION DE LOS DATOS
 
  /////Configuracion de horas////////
  lcd.setCursor(1,0);
  lcd.print("Confi. Dosis 3");
  lcd.setCursor(0,1); lcd.print("Horas:");
  for(int i=0; i < 2; i++){
  lcd.setCursor(10,1); 
  lcd.print(h6[0]); lcd.print(h6[1]);
  h6[i] = teclado.waitForKey();
  horasc2d3 = atof(h6);
  if(horasc2d3 > 24){
  i=-1;   
  h6[0] = '-'; h6[1] = '-';
  lcd.setCursor(10,1); lcd.print(h6[0]); lcd.print(h6[1]);
  }
  }
  banderita_5 = "F";
  lcd.clear();
  h6[0] = '-'; h6[1] = '-';
  s6[0] = '-'; s6[1] = '-';
  break;
  default:
  banderita_5 = "M";
  banderita_4 = "M";
  banderita_3 = "M";
  break; 
  }
  lcd.clear();
  bandera = true;
  } 
  break;
  case '3':                ///COMPARTIMIENTO #3
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Comparti. (C)");
  lcd.setCursor(0,1);
  lcd.print("Dosis 1) 2) 3)");
  lcd.setCursor(10,1); 
  while(bandera == false){
  teclita_3 = teclado.waitForKey();
  switch (teclita_3){                 
  case '1':
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Confi. Dosis 1");
  lcd.setCursor(0,1); lcd.print("Minutos:");
  lcd.setCursor(10,1); 
  lcd.print(s7[0]);   lcd.print(s7[1]);
  for(int i=0; i < 2; i++){
  s7[i] = teclado.waitForKey();
  lcd.setCursor(10,1); 
  lcd.print(s7[0]);  lcd.print(s7[1]);
  minutosc3d1 = atof(s7);
  if(minutosc3d1 > 60){
  i=-1;  
  s7[0] = '-'; s7[1] = '-';
  lcd.setCursor(10,1);
  lcd.print(s7[0]);   lcd.print(s7[1]);
  }
  }
  lcd.clear(); s7[0] = ' '; s7[1] = ' ';   ///EVITA COCATENACION DE LOS DATOS
 
  /////Configuracion de horas////////
  lcd.setCursor(1,0);
  lcd.print("Confi. Dosis 1");
  lcd.setCursor(0,1); lcd.print("Horas:");
  for(int i=0; i < 2; i++){
  lcd.setCursor(10,1); 
  lcd.print(h7[0]);  lcd.print(h7[1]);
  h7[i] = teclado.waitForKey();
  horasc3d1 = atof(h7);
  if(horasc3d1 > 24){
  i=-1;   
  h7[0] = '-'; h7[1] = '-';
  lcd.setCursor(10,1); lcd.print(h7[0]);   lcd.print(h7[1]);
  }
  }
  banderita_6 = "G";
  lcd.clear();
  s7[0] = '-'; s7[1] = '-'; 
  h7[0] = '-'; h7[1] = '-';
  break;
  case '2': 
  lcd.clear(); 
  lcd.setCursor(1,0);
  lcd.print("Confi. Dosis 2");
  lcd.setCursor(0,1); lcd.print("Minutos:");
  lcd.setCursor(10,1); 
  lcd.print(s8[0]);  lcd.print(s8[1]);
  for(int i=0; i < 2; i++){
  s8[i] = teclado.waitForKey();
  lcd.setCursor(10,1); 
  lcd.print(s8[0]);  lcd.print(s8[1]);
  minutosc3d2 = atof(s8);
  if(minutosc3d2 > 60){
  i=-1;  
  s8[0] = '-'; s8[1] = '-';
  lcd.setCursor(10,1);
  lcd.print(s8[0]);  lcd.print(s8[1]);
  }
  }
  lcd.clear(); s8[0] = ' '; s8[1] = ' ';   ///EVITA COCATENACION DE LOS DATOS
  /////Configuracion de horas////////
  lcd.setCursor(1,0);
  lcd.print("Confi. Dosis 2");
  lcd.setCursor(0,1); lcd.print("Horas:");
  for(int i=0; i < 2; i++){
  lcd.setCursor(10,1); 
  lcd.print(h8[0]);  lcd.print(h8[1]);
  h8[i] = teclado.waitForKey();
  horasc3d2 = atof(h8);
  if(horasc3d2 > 24){
  i=-1;   
  h8[0] = '-'; h8[1] = '-';
  lcd.setCursor(10,1); lcd.print(h8[0]);  lcd.print(h8[1]);
  }
  }
  banderita_7 = "H";
  lcd.clear();
  s8[0] = '-'; s8[1] = '-';
  h8[0] = '-'; h8[1] = '-';
  break;
  case '3': 
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Confi. Dosis 3");
  lcd.setCursor(0,1); lcd.print("Minutos:");
  lcd.setCursor(10,1); 
  lcd.print(s9[0]); lcd.print(s9[1]);
  for(int i=0; i < 2; i++){
  s9[i] = teclado.waitForKey();
  lcd.setCursor(10,1); 
  lcd.print(s9[0]); lcd.print(s9[1]);
  minutosc3d3 = atof(s9);
  if(minutosc3d3 > 60){
  i=-1;  
  s9[0] = '-'; s9[1] = '-';
  lcd.setCursor(10,1);
  lcd.print(s9[0]); lcd.print(s9[1]);
  }
  }
  lcd.clear(); s9[0] = ' '; s9[1] = ' ';   ///EVITA COCATENACION DE LOS DATOS
 
  /////Configuracion de horas////////
  lcd.setCursor(1,0);
  lcd.print("Confi. Dosis 3");
  lcd.setCursor(0,1); lcd.print("Horas:");
  for(int i=0; i < 2; i++){
  lcd.setCursor(10,1); 
  lcd.print(h9[0]); lcd.print(h9[1]);
  h9[i] = teclado.waitForKey();
  horasc3d3 = atof(h9);
  if(horasc3d3 > 24){
  i=-1;   
  h9[0] = '-'; h9[1] = '-';
  lcd.setCursor(10,1);  lcd.print(h9[0]); lcd.print(h9[1]);
  }
  }
  banderita_8 = "I";
  lcd.clear();
  s9[0] = '-'; s9[1] = '-';
  h9[0] = '-'; h9[1] = '-';
  break;
  default:
  banderita_8 = "M";
  banderita_7 = "M";
  banderita_6 = "M";
  break; 
  }
  lcd.clear();
  bandera = true;
  } 
  break; 
  default:
  bandera = true; 
  break; 

  case 'A':
  rellenar_compartimiento_A(); ////RELLENAR COMPARTIMIENTO #A
  bandera = true;
  lcd.clear();
  break; 

  case 'B':
  rellenar_compartimiento_B(); ////RELLENAR COMPARTIMIENTO #B
  bandera = true;
  lcd.clear();
  break;

  case 'C':
  rellenar_compartimiento_C(); ////RELLENAR COMPORTAMIENTO #C
  bandera = true;
  lcd.clear();
  break; 
  } //Aqui termina el switch (Puedes agregar mas opciones)
 }
 bandera = false;
  } 

  ///Compartimiento #1
  alarma_C1D1(fecha, segundos, horas, banderita); 
  alarma_C1D1(fecha, minutosc1d2, horasc1d2, banderita_1); 
  alarma_C1D1(fecha, minutosc1d3, horasc1d3, banderita_2); 

 ///Compartimiento #2
  alarma_C2D1(fecha, minutosc2d1, horasc2d1, banderita_3); 
  alarma_C2D1(fecha, minutosc2d2, horasc2d2, banderita_4); 
  alarma_C2D1(fecha, minutosc2d3, horasc2d3, banderita_5); 

 ///Compartimiento #3
  alarma_C3D1(fecha, minutosc3d1, horasc3d1, banderita_6); 
  alarma_C3D1(fecha, minutosc3d2, horasc3d2, banderita_7); 
  alarma_C3D1(fecha, minutosc3d3, horasc3d3, banderita_8); 
  }     




void rtc_inicializacion(){   ////Inicializacion del rtc
 if (! rtc.begin()) {
 //Serial.print("Modulo RTC no encontrado !"); 
 while (1);        
 }
// rtc.adjust(DateTime(__DATE__,__TIME__));
}

void lcd_inicializacion(){  ///Inicializacion del lcd 
lcd.begin(16,2);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Bienvenidos");
lcd.setCursor(0,1);
lcd.print("Pastillero Automatizado.");
delay(2000);
lcd.clear();
}

///CONTROL DE COMPARIMIENTO DE COMPARTIMIENTO #1
void alarma_C1D1(DateTime fecha, int minutos, int horas, String pivote){             /////Alarma 1 
  int rompe_ciclos_3000 = 0;
  int rompe_ciclos_4000 = 0;
  int favor = 0;
  

if ( fecha.hour() == horas && fecha.minute() == minutos && (pivote == "A" or pivote == "B" or pivote == "C")){ 
      if(pivote == "A"){
      lcd.clear();
      lcd.print( "A.Dosis 1 (A)" ); 
      lcd.setCursor(1,2); lcd.print("EXIT (6)"); 
      }

      if(pivote == "B"){
      lcd.clear();
      lcd.print( "A.Dosis 2 (A)" ); 
      lcd.setCursor(1,2); lcd.print("EXIT (6)"); 
      }

      if(pivote == "C"){
      lcd.clear();
      lcd.print( "A.Dosis 3 (A)" ); 
      lcd.setCursor(1,2); lcd.print("EXIT (6)");
      }


      //Gira al compartimiento A
      while(rompe_ciclos_3000 != 5){
      servito.write(99);
      if(digitalRead(3) == LOW){
      //delay(15);
      servito.write(90);
      rompe_ciclos_3000 = 5;
      } 
      }

      
      while(favor != 5){ 
       for (int i = 0; i < 8; i++) {  
      int duracion = 600 / duraciones[i];    // duracion de la nota en milisegundos
      tone(BUZZER_PASIVO, melodia[i], duracion);  // ejecuta el tono con la duracion
      int pausa = duracion * 1.30;      // calcula pausa
      delay(pausa);         // demora con valor de pausa
      noTone(BUZZER_PASIVO);        // detiene reproduccion de tono

       if (teclado.getKey()=='6'){  ///Rompo el ciclo 
              favor =5;
              i=9;
            } 
    }           
     }

     ///REGRESA A DONDE ESTA TAPADO
      while(rompe_ciclos_4000 != 5){    ////rompe_ciclos_4000 != 5
      servito.write(69);
      if(digitalRead(7) == LOW){
      //delay(10);
      servito.write(90);
      rompe_ciclos_4000 = 5;
      } 
      }

    if(rompe_ciclos_4000 == 5){
     banderita = "M";
     banderita_1 = "M";
     banderita_2 = "M";
     bandera = false;
     }
     
    // favor = 0;
     lcd.clear();
  }
}


////CONTROL DE ALARMAS PARA COMPARTIMIENTO #2

void alarma_C2D1(DateTime fecha, int minutos, int horas, String pivote){     
  int rompe_ciclos_5000 = 0;
  int rompe_ciclos_6000 = 0;
  int favor = 0;
if ( fecha.hour() == horas && fecha.minute() == minutos && (pivote == "D" or pivote == "E" or pivote == "F")){ 
      if(pivote == "D"){
      lcd.clear();
      lcd.print( "A.Dosis 1 (B)" ); 
      lcd.setCursor(1,2); lcd.print("EXIT (6)"); 
      }

      if(pivote == "E"){
      lcd.clear();
      lcd.print( "A.Dosis 2 (B)" ); 
      lcd.setCursor(1,2); lcd.print("EXIT (6)"); 
      }

      if(pivote == "F"){
      lcd.clear();
      lcd.print( "A.Dosis 3 (B)" ); 
      lcd.setCursor(1,2); lcd.print("EXIT (6)");
      }

      ////REALIZA GIRO A COMPARTIMIENTO B
      while(rompe_ciclos_5000 != 5){
      servito.write(99);
      if(digitalRead(4) == LOW){
      //delay(15);
      servito.write(90);
      rompe_ciclos_5000 = 5;
      } 
      }
      
      while(favor != 5){ 
       for (int i = 0; i < 8; i++) {  
      int duracion = 600 / duraciones[i];    // duracion de la nota en milisegundos
      tone(BUZZER_PASIVO, melodia[i], duracion);  // ejecuta el tono con la duracion
      int pausa = duracion * 1.30;      // calcula pausa
      delay(pausa);         // demora con valor de pausa
      noTone(BUZZER_PASIVO);        // detiene reproduccion de tono

       if (teclado.getKey()=='6'){  ///Rompo el ciclo 
              favor =5;
              i=9;
            } 
    }           
     }

     ////REGRESA LA TAPON DE B a A
      while(rompe_ciclos_6000 != 5){
      servito.write(69);
      if(digitalRead(7) == LOW){
      //delay(10);
      servito.write(90);
      rompe_ciclos_6000 = 5;
      } 
      }

      if(rompe_ciclos_6000 == 5){
       banderita_3 = "M";
       banderita_4 = "M";
       banderita_5 = "M";
       bandera = false;
     }
     
     //favor = 0;
     lcd.clear();
  }
}


///CONTROL DE ALARMA COMPARTIMIENTO #3
void alarma_C3D1(DateTime fecha, int minutos, int horas, String pivote){     
  int rompe_ciclos_7000 = 0;
  int rompe_ciclos_8000 = 0;
  int favor = 0;
if ( fecha.hour() == horas && fecha.minute() == minutos && (pivote == "G" or pivote == "H" or pivote == "I") ){ 
      if(pivote == "G"){
      lcd.clear();
      lcd.print( "A.Dosis 1 (C)" ); 
      lcd.setCursor(1,2); lcd.print("EXIT (6)"); 
      }

      if(pivote == "H"){
      lcd.clear();
      lcd.print( "A.Dosis 2 (C)" ); 
      lcd.setCursor(1,2); lcd.print("EXIT (6)"); 
      }

      if(pivote == "I"){
      lcd.clear();
      lcd.print( "A.Dosis 3 (C)" ); 
      lcd.setCursor(1,2); lcd.print("EXIT (6)");
      }

      ///MANDA A COMPARTIMIENTO C
       ////REGRESA LA TAPON 
      while(rompe_ciclos_7000 != 5){
      servito.write(69);
      if(digitalRead(5) == LOW){
      servito.write(90);
      rompe_ciclos_7000 = 5;
      } 
      }
      
      
      while(favor != 5){ 
       for (int i = 0; i < 8; i++) {  
      int duracion = 600 / duraciones[i];    // duracion de la nota en milisegundos
      tone(BUZZER_PASIVO, melodia[i], duracion);  // ejecuta el tono con la duracion
      int pausa = duracion * 1.30;      // calcula pausa
      delay(pausa);         // demora con valor de pausa
      noTone(BUZZER_PASIVO);        // detiene reproduccion de tono

       if (teclado.getKey()=='6'){  ///Rompo el ciclo 
              favor =5;
              i=9;
            } 
    }           
     }

    ////REGRESA AL TAPON 
      while(rompe_ciclos_8000 != 5){
      servito.write(99);
      if(digitalRead(7) == LOW){
      ///delay(15);
      servito.write(90);
      rompe_ciclos_8000 = 5;
      } 
      }

         if(rompe_ciclos_8000 == 5){
             banderita_6 = "M";
              banderita_7 = "M";
              banderita_8 = "M";
              bandera = false;
     }
     
     //favor = 0;
     lcd.clear();
  }
}

void rellenar_compartimiento_A(void){
  int rompeciclo_ida = 0;
  int rompeciclo_regreso = 0;
  int okay = 0;
  lcd.clear();
  lcd.setCursor(1,0); 
  lcd.print("Rellenar Com.A"); 
 
  while(rompeciclo_ida != 5){
   servito.write(99);
   if(digitalRead(3) == LOW){
    //delay(15);
    servito.write(90);
    rompeciclo_ida = 5;
   }
  }

 lcd.setCursor(1,1); 
 lcd.print("(6)LISTO");

 while(okay != 5){
     if (teclado.getKey()=='6'){  ///Rompo el ciclo 
           okay = 5;
            }
 }
  

 while(rompeciclo_regreso != 5){
   servito.write(69);
   if(digitalRead(7) == LOW){
    //delay(10);
    servito.write(90);
    rompeciclo_regreso = 5;
   }
  }
 
}

void rellenar_compartimiento_B(void){
  int rompeciclo_ida = 0;
  int rompeciclo_regreso = 0;
  int okay = 0;
  lcd.clear();
  lcd.setCursor(1,0); 
  lcd.print("Rellenar Com.B"); 
 
  while(rompeciclo_ida != 5){
   servito.write(99);
   if(digitalRead(4) == LOW){
    //delay(15);
    servito.write(90);
    rompeciclo_ida = 5;
   }
  }

 lcd.setCursor(1,1); 
 lcd.print("(6)Listo"); 

  while(okay != 5){
     if (teclado.getKey()=='6'){  ///Rompo el ciclo 
           okay = 5;
            }
 }


 while(rompeciclo_regreso != 5){
   servito.write(69);
   if(digitalRead(7) == LOW){
    //delay(15);
    servito.write(90);
    rompeciclo_regreso = 5;
   }
  }
 
  
}

void rellenar_compartimiento_C(void){
  int rompeciclo_ida = 0;
  int rompeciclo_regreso = 0;
  int okay = 0;
  lcd.clear();
  lcd.setCursor(1,0); 
  lcd.print("Rellenar Com.C"); 
 
  while(rompeciclo_ida != 5){
   servito.write(69);
   if(digitalRead(5) == LOW){
    //delay(10);
    servito.write(90);
    rompeciclo_ida = 5;
   }
  }

 lcd.setCursor(1,1); 
 lcd.print("(6)Listo"); 

  while(okay != 5){
     if (teclado.getKey()=='6'){  ///Rompo el ciclo 
           okay = 5;
            }
 }


 while(rompeciclo_regreso != 5){
   servito.write(99);
   if(digitalRead(7) == LOW){
    //delay(15);
    servito.write(90);
    rompeciclo_regreso = 5;
   }
  } 
}


/*void temp(){
  double temperatura=0;
  status = bmp180.startTemperature();
  delay(status);
  status = bmp180.getTemperature(temperatura);
  float valor = temperatura; 
  lcd.setCursor(11,0); 
  lcd.print("C:"); lcd.print(temperatura);
}
*/
