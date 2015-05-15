//debug.h
void initializeDebug()
{
  // Serial.begin(9600);
}
//---------------------------------------------------------------------
//update the blinking led
inline void ledUpdate()
{
  static int ledState = HIGH;
  LEDTimer.updateTimer();
  if (LEDTimer.timerDone())
  {
  sendLEDdata(3, 0);
    ledState = !ledState;
    digitalWrite(13, ledState);
  }
}

void updateDebug()
{
  //      Serial.println("");
  //      Serial.print("In MACRO Mode:  ");
  //      Serial.println(internalMacroKeeper);
  //      Serial.println("");
  //      Serial.println("------From Comm Data----");
  //      Serial.print("macro_command:  ");
  //      Serial.println(commandBack.macro_command);
  static Timers debugTimer(1000);
  if(debugTimer.timerDone()){
    //      Serial.print("encoderL:  ");
    //      Serial.println(encoderL);
    //      Serial.print("encoderR:  ");
    //      Serial.println(encoderR);
    //      Serial.print("encoderSpeedL:  ");
    //      Serial.println(encoderSpeedL);
    //      Serial.print("encoderSpeedR:  ");
    //      Serial.println(encoderSpeedR);
    
      Serial.print("encoderValue:  ");
      Serial.println(encoderValue);
    
    //      Serial.println("");
    //      Serial.println("");
    //
//
//    Serial.print("gyroScope:  ");
//    Serial.println(commandBack.gyro);


  }
}







