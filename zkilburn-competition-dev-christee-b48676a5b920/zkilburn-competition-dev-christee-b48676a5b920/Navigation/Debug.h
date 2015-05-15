//Debug.h

//USB DEBUG
inline void USBdebug()
{
  static Timers verboseTime(500);
  verboseTime.updateTimer();

  if (verboseTime.timerDone()) {
    //    Serial.print("volts: ");
    //    Serial.println(Nav.volts);
    //    Serial.print("amps: ");
    //    Serial.println(Nav.amps);
    //    Serial.print("amphour: ");
    //    Serial.println(Nav.amphour);    
    //    Serial.print ("Gyro 1: ");
    //    Serial.println(gyro1.updateGyro());
    //    Serial.println(" ");
    //    Serial.print ("Gyro 2: ");
    //    Serial.println(gyro2.updateGyro());
    //    Serial.println(" ");
    //    Serial.print("Lng Front: ");
    //    Serial.println(frontS);
    //    Serial.print("Lng Back: ");
    //    Serial.println(backS);
    //    Serial.print("Lng Right: ");
    //    Serial.println(rightS);
    //    Serial.print("Lng Left ");
    //    Serial.println(leftS);
    //    Serial.print("Medium Front Left: ");
    //    Serial.println(IRSFL);
    //    Serial.print("Medium Front Right: ");
    //    Serial.println(IRSFR);
    //    Serial.print("Medium Left: ");
    //    Serial.println(IRML);`
    //    Serial.print("Medium Right: ");
    //    Serial.println(IRMR);
    //    Serial.print("Medium Back: ");
    //    Serial.println(IRMB);
    //    Serial.print("Short Back Left: ");
    //    Serial.println(IRSBL);
    //    Serial.print("Short Back Right: ");
    //    Serial.println(IRSBR);
  }
}



