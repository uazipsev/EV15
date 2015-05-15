//pins.h
#define ACTUATOR_FEEDBACK A3
#define ANGLE_OFFSET 7
#define VOLT_OFFSET 0.1
#define ANGLE_RANGE 90.0
#define VOLT_RANGE 3.0
#define MAX_VOLT 5.0
#define MAX_ADC 1023.0
int i = 0;
unsigned int ang[6];
unsigned int total = 0;
unsigned int avg = 0;

void initializeLed()
{
  pinMode(ACTUATOR_FEEDBACK,INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13,HIGH);
  pinMode(vibrate,OUTPUT);
  digitalWrite(vibrate,HIGH);
}

  
inline void updateLed(){ 
  static Timers LEDTimer(1000);
  if(LEDTimer.timerDone())
    digitalWrite(13, !digitalRead(13));
  
}

 inline void updateOffset(){  
   if((bucketAngle >= VIBRATING_MOTOR_ON_HIGH)||(bucketAngle<=VIBRATING_MOTOR_ON_LOW)){
     digitalWrite(A4,LOW); 
   }
   else{
     digitalWrite(A4,HIGH); 
   }
 }
 
 inline int updateAngle(){
   
    
    int raw= analogRead(ACTUATOR_FEEDBACK);
    float volts = ((raw / MAX_ADC) * MAX_VOLT) - VOLT_OFFSET;
    int angle = (volts * (ANGLE_RANGE / VOLT_RANGE))-ANGLE_OFFSET;
   return angle;
 }
