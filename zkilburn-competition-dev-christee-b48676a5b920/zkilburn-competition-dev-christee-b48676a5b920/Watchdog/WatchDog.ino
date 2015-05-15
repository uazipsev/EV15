#include <Timers.h>

//pin numbers on the ATMEGA 328 for the parts needed for the watchdog
#define PIC13              3
#define PN13               6
#define OPTOISO_5VSENEN    A0
#define OPTOISO_5VLEDEN    A1
#define OPTOISO_5VEN       A2
#define OPTOISO_9VEN       A3
int pic13Val;
int pn13Val;
const int pin = 13;
Timers wdogtimer(500);

void setup(){
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
  pic13Val = digitalRead(PIC13);
  pn13Val = digitalRead(PN13);
  pinMode(OPTOISO_5VSENEN, OUTPUT);
  pinMode(OPTOISO_5VLEDEN, OUTPUT);
  pinMode(OPTOISO_5VEN, OUTPUT);
  pinMode(OPTOISO_9VEN, OUTPUT);
}

void loop (){
  digitalWrite(pin,HIGH);
  if(wdogtimer.timerDone()){
    //if hanging then stop sending power for 1/2 sec
    if(pic13Val == digitalRead(PIC13))
    {
      digitalWrite(OPTOISO_5VSENEN, HIGH);
      digitalWrite(OPTOISO_5VLEDEN, HIGH);
      digitalWrite(OPTOISO_5VEN, HIGH);
      digitalWrite(OPTOISO_9VEN, HIGH);
    }
    if(pn13Val == digitalRead(PN13))
    {
      digitalWrite(OPTOISO_5VSENEN, HIGH);
      digitalWrite(OPTOISO_5VLEDEN, HIGH);
      digitalWrite(OPTOISO_5VEN, HIGH);
      digitalWrite(OPTOISO_9VEN, HIGH);
    } 

    while(!wdogtimer.timerDone()){
      wdogtimer.updateTimer();
    }
    //reset all power   
    digitalWrite(OPTOISO_5VSENEN, LOW);
    digitalWrite(OPTOISO_5VLEDEN, LOW);
    digitalWrite(OPTOISO_5VEN, LOW);
    digitalWrite(OPTOISO_9VEN, LOW);
    digitalWrite(pin, LOW);
  }
  // continue the timer checking
  wdogtimer.updateTimer();
}

