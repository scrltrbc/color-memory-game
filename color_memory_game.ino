//pinul la care este conectat buzzer-ul
#define PIN_BUZZER 7 

#define NIVEL_MAX 100

#define NR_BECURI 4

#define NOTE_B0  31
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

const byte pini_becuri[]={3, 6, 10, 13};
const byte pini_butoane[]={2, 5, 9, 12};

const int note_culori[]={ NOTE_G3, NOTE_C4, NOTE_E4, NOTE_G5};

/*un tablou in  care memoram modelul nivelului curent,
  la fiecare nivel se va mai adauga o culoar,
  iar la finalul jocului se va reseta
*/

byte model_nivel[NIVEL_MAX] = {0};
byte nivel = 0;

//functie de startup ce initializeaza componentele
void setup()
{
  for (byte i=0; i<NR_BECURI; ++i)
  {
    pinMode(pini_becuri[i], OUTPUT);
    pinMode(pini_butoane[i], INPUT_PULLUP);
  }
  pinMode(PIN_BUZZER, OUTPUT);
}


//functie ce aprinde un bec si emite sunetul corespunzator
void aprindere_si_sunet(byte bec)
{
  digitalWrite(pini_becuri[bec], HIGH);
  tone(PIN_BUZZER, note_culori[bec]);
  delay(300);
  digitalWrite(pini_becuri[bec], LOW);
  noTone(PIN_BUZZER);
}


//functie ce reda modelul unui nivel
void redare_model_nivel()
{
  for (int i=0; i<nivel; ++i)
  {
    byte bec_curent= model_nivel[i];
    aprindere_si_sunet(bec_curent);
    delay(500);
  }
}


//functie ce citeste butonul apasat
byte apasa_un_buton()
{
  while (true)
  {
    for (byte i=0; i<4; ++i)
    {
      if (digitalRead(pini_butoane[i])==LOW)
        return i;
    }
    delay(1);
  }
}


//functie ce verifica daca butonul apasat este corect
bool verificare_buton_apasat()
{
  for (int i= 0; i<nivel; ++i)
  {
    byte buton_corect= model_nivel[i];
    byte buton_apasat= apasa_un_buton();
    aprindere_si_sunet(buton_apasat);
    if (buton_apasat!=buton_corect)
      return false;
  }

  return true;
}

//reda sunetul de sfarsit de joc
void game_over()
{
  for(byte i=0; i<NR_BECURI; ++i)
   digitalWrite(pini_becuri[i], HIGH);
  delay(300);
  for(byte i=0; i<4; ++i)      
   digitalWrite(pini_becuri[i], LOW);
  tone(PIN_BUZZER, NOTE_DS5);
  delay(300);
  tone(PIN_BUZZER, NOTE_D5);
  delay(300);
  tone(PIN_BUZZER, NOTE_CS5);
  delay(300);
  for (byte i=0; i<10; ++i)
  {
    for (int pitch=-10; pitch<=10; ++pitch)
    {
      tone(PIN_BUZZER, NOTE_C5 + pitch);
      delay(5);
    }
  }
  noTone(PIN_BUZZER);
  delay(500);
}



//functie ce emite sunetul de level-up
void level_up()
{
  tone(PIN_BUZZER, NOTE_E4);
  delay(150);
  tone(PIN_BUZZER, NOTE_G4);
  delay(150);
  tone(PIN_BUZZER, NOTE_E5);
  delay(150);
  tone(PIN_BUZZER, NOTE_C5);
  delay(150);
  tone(PIN_BUZZER, NOTE_D5);
  delay(150);
  tone(PIN_BUZZER, NOTE_G5);
  delay(150);
  noTone(PIN_BUZZER);
}


//functia "principala" care loop-uieste jocul
void loop()
{
  if(nivel==0)
 {
   
   byte buton=4;
   buton=apasa_un_buton();
   if(buton<4)
   {
     tone(PIN_BUZZER, NOTE_A6);
     
     for(byte i=0; i<NR_BECURI; ++i)
      digitalWrite(pini_becuri[i], HIGH);
     delay(300);
     for(byte i=0; i<4; ++i)      
  	  digitalWrite(pini_becuri[i], LOW);
 
      noTone(PIN_BUZZER);
     
      level_up();
    }
    delay(300);
  }
 
  model_nivel[nivel]=random(0,4);
  nivel++;
  if(nivel >= NIVEL_MAX)
  {
    nivel=0;
  }

  redare_model_nivel();
  if(!verificare_buton_apasat())
  {
    game_over();
    nivel=0;
  }

  delay(300);

  if(nivel > 0)
  {
    level_up();
    delay(300);
  }
}
