//pins.h

#define VMSP 80
#define VMSP2 10
int angle = 0;
int i = 0;
unsigned int ang[6];
unsigned int total = 0;
unsigned int avg = 0;

void initializeLed()
{
  pinMode(13, OUTPUT);
  digitalWrite(13,HIGH);
  pinMode(vibrate,OUTPUT);
  digitalWrite(vibrate,HIGH);
}

static unsigned long previous = 0;
static unsigned long current = 0;
static int state = HIGH; 
  
inline void updateLed(){ 
  current = millis();  
  if(abs(current - previous) > 1000)
  {
    previous = current;
    state = !state;
   
    digitalWrite(13, state);
  }  
}

 inline void updateOffset(){  
   if((angle >= VMSP)||(angle<=VMSP2)){
     digitalWrite(A4,LOW); 
   }
   else{
     digitalWrite(A4,HIGH); 
   }
 }
 
 inline int updateAngle(){
//   total=0;
//   for(i=1;i<=1;i++){
//      ang[i-1] = ang[i];
//   }
//   ang[1] = analogRead(A3);
//   for(i=0;i<=1;i++){
//      total = total + ang[i];
//   } 
//   avg = total/2;
//   
//  
//   
//   float volts = ((avg / 1023.0) * 5.0) - 0.1;
//   angle = (volts * (90.0 / 3.0))-5;
//   
    int raw= analogRead(A3);
    float volts = ((raw / 1023.0) * 5.0) - 0.1;
    angle = (volts * (90.0 / 3.0))-5;
//    Serial.print("Commanded: ");
//    Serial.print(actuatorValue);
//    Serial.print("  Volts:  ");
//    Serial.print(volts);
//    Serial.print("  Current Angle:  ");
//    Serial.println(angle);
   return angle;
 }
