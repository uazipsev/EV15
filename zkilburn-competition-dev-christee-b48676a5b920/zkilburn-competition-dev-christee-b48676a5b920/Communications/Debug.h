//debug.h
int verbosed = 0;
void initializeDebug()
{
  //Serial.begin(9600);
}
void toggleLED()
{
  digitalWrite(13, !digitalRead(13));
}

void updateDebug()
{

  static Timers verboseTime(200);
  verboseTime.updateTimer();

  if (verboseTime.timerDone()) {
//    //switch to the debug line for debug verbose
    selectCommLines(DEBUGcomm);
//    delay(15);          //let it settle a minute
//
//    //Puke out the data
//    Serial2.println("");
//    if (macro_command != 0) {
//      Serial2.print("______________In MACRO Mode:  ");
//      Serial2.println(macro_command);
//    }
//
//    else {
//      Serial2.print("______________Macro NOT ACTIVE");
//      Serial2.println("");
//    }
//
//    Serial2.print("macro_command from Control:  ");
//    Serial2.println(macro_command);
//    Serial2.print("macro_command from Nav:  ");
//    Serial2.println(fromNav.macro_command);
//    Serial2.println("");
//    Serial2.println("------From Nav Data----");
//    Serial2.print("macro_command:  ");
//    Serial2.println(fromNav.macro_command);
//    Serial2.print("macro_sub_command:  ");
//    Serial2.println(fromNav.macro_sub_command);
//    Serial2.print("macro_complete:  ");
//    Serial2.println(fromNav.macro_complete);
//    Serial2.println("");
//    Serial2.println("");
//    Serial2.println("------From Control Data----");
//    Serial2.print("macro_command:  ");
//    Serial2.println(fromControl.macro_command);
//    Serial2.print("macro_stop:  ");
//    Serial2.println(fromControl.macro_stop);
//    Serial2.println("");
//    Serial2.println("");
    //allow data to get through the system before changing back to LED
//
//    delay(15);

    selectCommLines(LEDcomm);


  }
}




