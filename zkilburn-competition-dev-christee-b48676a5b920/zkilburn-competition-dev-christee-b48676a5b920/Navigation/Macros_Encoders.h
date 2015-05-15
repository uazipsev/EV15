//macros_encoders.h

#define encoderKp 2
#define encoderKi 0
#define encoderKd 0



void encoderRun1()
{ 
  while(macro_stop!=1)
  {
    runEncoderDistanceEvenly(50);
    doTurn(90); 
  }
}

void encoderRun2()
{
  wipeEncoders();
  while (((encoderL < 40) || (encoderR < 40)) && (macro_stop != 1))
  {
    static Timers motorSend(50);
    if(MPUTimer.timerDone()) updateMPU();
    if (motorSend.timerDone())
    {
      sendMotorCommand(15,-15);//(leftMotor,rightMotor)
    }
    macroCommunicationsUpdate();
  }
  allStop();
  motor_unStick();
  wipeEncoders();
}

void encoderRun3()
{
  //turns the opposite way 90 degrees hypothetically with small correction at the end to make sure square
  // possibility of using Gyro
  wipeEncoders();
  int inEncoderL = 0;
  int inEncoderR =0;
  static Timers motorSend(50);
  while (((inEncoderL < 20) || (inEncoderR < 20)) && (macro_stop != 1))
  {
    if(MPUTimer.timerDone()) updateMPU();
    if (motorSend.timerDone())
    {      
      sendMotorCommand(-15,15);//(leftMotor,rightMotor)
    }
    inEncoderL+=encoderL;
    inEncoderR+=encoderR;
    wipeEncoders();
    macroCommunicationsUpdate();
  }
  float encoderDif = inEncoderL-inEncoderR;
  //makes sure that the encoders are ending up at the same distance to ensure that robot ends up flush
  while(((encoderDif >3) || (encoderDif<-3)) && (macro_stop != 1))
  {
    if(MPUTimer.timerDone()) updateMPU();
    //    Serial.print("EncoderDiff: ");
    //    Serial.println(encoderDif);
    if(motorSend.timerDone()){
      //if the left encoder is bigger than the right encoder
      if(encoderDif>3)
      {
        //have to continure the turn in the same direction
        sendMotorCommand(-2,10);//(leftMotor,rightMotor)
        inEncoderL-=encoderL;
        inEncoderR+=encoderR;
      }
      //if the right encoder is bigger than the left encoder
      if(encoderDif<3)
      {
        //have to continure the turn in the same direction
        sendMotorCommand(-10,2);//(leftMotor,rightMotor)
        inEncoderL+=encoderL;
        inEncoderR-=encoderR;
      }
      encoderDif = inEncoderL-inEncoderR;
      wipeEncoders();
    }
    macroCommunicationsUpdate();
  }
  allStop();
  motor_unStick();
  wipeEncoders();
}

void encoderRun5()
{
  while(macro_stop!=1)
  {
    runEncoderDistanceEvenly(100);   
    runEncoderDistanceEvenly(-100);
  }
}

void runRightEncoder(int cm)
{
  wipeEncoders();
  //Position PID loop to target an end distance
  PID output(cm, encoderKp, encoderKi, encoderKd, 2);
  PIDTimer.resetTimer();
  while((encoderR<abs(cm)) && (macro_stop != 1))
  {

    if(MPUTimer.timerDone()) updateMPU();
    if(PIDTimer.timerDone())
    {
      motorOutputControlRight(output.updateOutput(encoderR));
      //output.verboseCalc();
    }

    macroCommunicationsUpdate();    
  }

  allStop();
  motor_unStick();
  wipeEncoders();
}

void runLeftEncoder(int cm)
{
  wipeEncoders();
  //Position PID loop to target an end distance
  PID output(cm, encoderKp, encoderKi, encoderKd, 2);
  PIDTimer.resetTimer();
  while(((encoderL<abs(cm))) && (macro_stop != 1))
  {

    if(MPUTimer.timerDone()) updateMPU();
    if(PIDTimer.timerDone())
    {
      motorOutputControlLeft(output.updateOutput(encoderL));
      //output.verboseCalc();
    }

    macroCommunicationsUpdate();    
  }

  allStop();
  motor_unStick();
  wipeEncoders();
}

void runEncoderDistance(int cm)
{
  wipeEncoders();
  //Position PID loop to target an end distance
  PID output(abs(cm), encoderKp, encoderKi, encoderKd, 2);
  PIDTimer.resetTimer();
  while(((encoderL<abs(cm))||(encoderR<abs(cm))) && (macro_stop != 1))
  {

    if(MPUTimer.timerDone()) updateMPU();
    if(PIDTimer.timerDone())
    {
      if(cm>0)
        motorOutputControl(output.updateOutput((encoderL+encoderR)/2));
      else       
        motorOutputControl(-output.updateOutput((encoderL+encoderR)/2));
      //output.verboseCalc();
    }

    macroCommunicationsUpdate();    
  }

  allStop();
  motor_unStick();
  wipeEncoders();
}

#define GYRO true
#define NOGYRO false

void runEncoderDistanceEvenly(float cm)
{
  //if(cm<0)  cm=cm*0.877;
  gyroF1.zeroInternalAngle();
  gyroF2.zeroInternalAngle();
  macroAngle=0;
  wipeEncoders();
  //Position PID loop to target an end distance
  PID output(abs(cm), encoderKp, encoderKi, encoderKd, 2);
  PIDTimer.resetTimer();
  while(((encoderL<abs(cm))||(encoderR<abs(cm))) && (macro_stop != 1))
  {

    
    if(MPUTimer.timerDone()) updateMPU();
    if(PIDTimer.timerDone())
    {
    //Serial.println("IN MACRO");  
      if(encoderL==encoderR)
      {
        if(cm>0)
            motorOutputControl(constrain(output.updateOutput(encoderL),0,75));
          else
            motorOutputControl(-constrain((output.updateOutput(encoderL)),0,75));
          
      }
      else
      {
        if(cm>0)
          motorOutputControlCorrect(constrain((output.updateOutput((encoderL+encoderR)/2.0)),0,75),encoderL,encoderR,GYRO);
        else
          motorOutputControlCorrect(-constrain((output.updateOutput((encoderL+encoderR)/2.0)),0,75),encoderL,encoderR,GYRO);
      }
    
    
     // output.verboseCalc();
    }

    macroCommunicationsUpdate();    
  }

  allStop();
  motor_unStick();
  //wipeEncoders();
}

void runEncoderDistanceDiggingly(float cm)
{
  if(cm<0)  cm=cm*0.877;
  gyroF1.zeroInternalAngle();
  gyroF2.zeroInternalAngle();
  macroAngle=0;
  wipeEncoders();
  //Position PID loop to target an end distance
  PID output(abs(cm), encoderKp, encoderKi, encoderKd, 2);
  PIDTimer.resetTimer();
  while(((encoderL<abs(cm))||(encoderR<abs(cm))) && (macro_stop != 1))
  {

    
    if(MPUTimer.timerDone()) updateMPU();
    if(PIDTimer.timerDone())
    {
    //Serial.println("IN MACRO");  
      if(encoderL==encoderR)
      {
        if(cm>0)
            motorOutputControlDig(constrain(output.updateOutput(encoderL),0,75));
          else
            motorOutputControlDig(-constrain((output.updateOutput(encoderL)),0,75));
          
      }
      else
      {
        if(cm>0)
          motorOutputControlCorrectDig(constrain((output.updateOutput((encoderL+encoderR)/2.0)),0,75),encoderL,encoderR,GYRO);
        else
          motorOutputControlCorrectDig(-constrain((output.updateOutput((encoderL+encoderR)/2.0)),0,75),encoderL,encoderR,GYRO);
      }
    
    
     // output.verboseCalc();
    }

    macroCommunicationsUpdate();    
  }

  allStop();
  motor_unStick();
  //wipeEncoders();
}


void wipeEncoders()
{
  encoderL = 0;
  encoderR = 0;
}

