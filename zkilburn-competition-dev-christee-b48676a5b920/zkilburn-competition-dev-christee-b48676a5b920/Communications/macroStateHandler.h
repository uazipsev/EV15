
void updateNav();
void updateControl();
void endMacroControl();
void toggleLED();
inline void endMacroNav();
void endMacroControl();
inline void finishMacro();
inline void updateScreen();
inline void initMacroSystem();

inline void macroUpdate()
{
  //START MACRO LOOP
  initMacroSystem();
  controlStop = 0;
  //GETSTUCK LOOP FOR AUTO MODE
  while ((macro_complete == 0) && (controlStop == 0))
  {
    
    //updateDebug();
    LEDtimer.updateTimer();
    if (LEDtimer.timerDone())
    {
      to_LED.sendData();
    }

    if (ControlBoard.receiveData())
    { //receive information
      macro_command           = controlReceive[MACRO_COMMAND_CONTROL_RECEIVE];
      macro_sub_command       = controlReceive[MACRO_SUB_COMMAND_CONTROL_RECEIVE];
      controlStop             = controlReceive[MACRO_STOP_CONTROL_RECEIVE];

      ControlBoard.ToSend(MACRO_COMPLETE_CONTROL_SEND, 0);
      ControlBoard.ToSend(MACRO_COMMAND_CONTROL_SEND, macro_command);
      ControlBoard.sendData(CONTROL_ADDRESS);

      //prepare information from the CONTROL board for the NAVIGATION
      NavigationBoard.ToSend(MACRO_COMMAND_NAV_SEND     , macro_command);
      NavigationBoard.ToSend(MACRO_SUB_COMMAND_NAV_SEND , macro_sub_command);
      NavigationBoard.ToSend(MACRO_STOP_NAV_SEND        , controlStop);
      NavigationBoard.sendData(NAVIGATION_ADDRESS);
    }
    if (NavigationBoard.receiveData())
    {
      //update the information to send to the CONTROL board
      ControlBoard.ToSend(AMPS_CONTROL_SEND         , navigationReceive[AMPS_NAV_RECEIVE]);
      ControlBoard.ToSend(AMPHOUR_CONTROL_SEND      , navigationReceive[AMPHOUR_NAV_RECEIVE]);
      ControlBoard.ToSend(VOLTS_CONTROL_SEND        , navigationReceive[VOLTS_NAV_RECEIVE]);
      ControlBoard.ToSend(ENCODERRIGHT_CONTROL_SEND , navigationReceive[ENCODERRIGHT_NAV_RECEIVE]);
      ControlBoard.ToSend(ENCODERLEFT_CONTROL_SEND  , navigationReceive[ENCODERLEFT_NAV_RECEIVE]);
      ControlBoard.ToSend(ENCODERSPEEDR_CONTROL_SEND, navigationReceive[ENCODERSPEEDR_NAV_RECEIVE]);
      ControlBoard.ToSend(ENCODERSPEEDL_CONTROL_SEND, navigationReceive[ENCODERSPEEDL_NAV_RECEIVE]);
      ControlBoard.ToSend(RIGHT_MOTOR_CONTROL_SEND  , navigationReceive[RIGHT_MOTOR_NAV_RECEIVE]);
      ControlBoard.ToSend(LEFT_MOTOR_CONTROL_SEND   , navigationReceive[LEFT_MOTOR_NAV_RECEIVE]);
      ControlBoard.ToSend(GYRO_CONTROL_SEND         , navigationReceive[GYRO_NAV_RECEIVE]);
      macro_complete                                = navigationReceive[MACRO_COMPLETE_NAV_RECEIVE];
      macro_sub_command                             = navigationReceive[MACRO_SUB_COMMAND_NAV_RECEIVE];
    }
    toggleLED();
    delay(15);
  }
  //EXIT AND FINISH MACRO LOOP
  finishMacro();
}

//---METHOD TO START A MACRO SYSTEM COMMAND------
inline void initMacroSystem()
{
  //Set LED state
  led.state = MACRO;
  to_LED.sendData();

  //Update Control Box
  updateControl();

  //Update Nav with System
  updateNav();

  macro_complete = 0;

 
}
//--------METHOD TO FINISH A MACRO SYSTEM COMMAND-------------
inline void finishMacro()
{
  //    selectCommLines(DEBUGcomm);
  //  Serial2.println("GOING TO STOP THE MACRO");
  //    selectCommLines(LEDcomm);
  endMacroControl();
  endMacroNav();
  delay(50);
  commTimer.resetTimer();
  //Return the Robot to drive mode
  currentState    = 1;
  macro_command   = 0;
  macro_complete  = 0;
  ControlBoard.ToSend(MACRO_COMPLETE_CONTROL_SEND, 0);
  ControlBoard.sendData(CONTROL_ADDRESS);
  led.state = MANUAL;
  to_LED.sendData();
}


//----------Starting Functions-----------------------------
void updateControl()
{
  
  ControlBoard.ToSend(MACRO_COMPLETE_CONTROL_SEND, 0);
  ControlBoard.ToSend(MACRO_COMMAND_CONTROL_SEND, macro_command);
  ControlBoard.sendData(CONTROL_ADDRESS);
  //    selectCommLines(DEBUGcomm);
  //  Serial2.println("Assumed the control heard us");
  //    selectCommLines(LEDcomm);
}

void updateNav()
{

  NavigationBoard.ToSend(MACRO_SUB_COMMAND_NAV_SEND , macro_sub_command);
  NavigationBoard.ToSend(MACRO_COMMAND_NAV_SEND     , macro_command);
  NavigationBoard.ToSend(MACRO_STOP_NAV_SEND        , 0);
  NavigationBoard.sendData(NAVIGATION_ADDRESS);
  delay(5);
  sender = 0;
  //make sure they hear us
  while ((navigationReceive[MACRO_COMMAND_NAV_RECEIVE] != macro_command))
  {
    //    selectCommLines(DEBUGcomm);
    //    Serial2.print("SENDING NAV MACRO: ");
    //    Serial2.println(macro_command);
    //    selectCommLines(LEDcomm);
    NavigationBoard.receiveData();

    sender += 1;
    delay(5);
    if (sender >= 10)
    {
      NavigationBoard.ToSend(MACRO_SUB_COMMAND_NAV_SEND , macro_sub_command);
      NavigationBoard.ToSend(MACRO_COMMAND_NAV_SEND     , macro_command);
      NavigationBoard.sendData(NAVIGATION_ADDRESS);
      sender = 0;
    }
  }
}

//-----------------------------Ending Functions---------------------
void endMacroControl() {
  //Tell the control box that macro complete (send to control)

  ControlBoard.ToSend(MACRO_COMMAND_CONTROL_SEND, 0);
  ControlBoard.ToSend(MACRO_COMPLETE_CONTROL_SEND, 1);
  ControlBoard.sendData(CONTROL_ADDRESS);
  delay(5);
  macro_command = 1;
  sender        = 0;
  while (macro_command != 0)
  {
    //    selectCommLines(DEBUGcomm);
    //    Serial2.print("ENDING MACRO CONTROL:  ");
    //    selectCommLines(LEDcomm);
    //    Serial2.println(macro_command);
    if (ControlBoard.receiveData())
    {
      macro_command = controlReceive[MACRO_COMMAND_CONTROL_RECEIVE];
    }
    sender += 1;
    delay(5);
    if (sender >= 10)
    {
      ControlBoard.ToSend(MACRO_COMMAND_CONTROL_SEND,  0);
      ControlBoard.ToSend(MACRO_COMPLETE_CONTROL_SEND, 1);
      ControlBoard.sendData(CONTROL_ADDRESS);
      sender = 0;
    }
  }

}

inline void endMacroNav()
{
  sender = 0;
  NavigationBoard.ToSend(MACRO_SUB_COMMAND_NAV_SEND , 0);
  NavigationBoard.ToSend(MACRO_COMMAND_NAV_SEND     , 0);
  NavigationBoard.ToSend(MACRO_STOP_NAV_SEND, 1);
  NavigationBoard.sendData(NAVIGATION_ADDRESS);

  navMacro = navigationReceive[MACRO_COMMAND_NAV_RECEIVE];
  while (navMacro != 0)
  {
    if (NavigationBoard.receiveData())
    {
      //    selectCommLines(DEBUGcomm);
      //    Serial2.println("ENDING NAV MACRO: ");
      //    Serial2.print(navMacro);
      //    selectCommLines(LEDcomm);
      navMacro = navigationReceive[MACRO_COMMAND_NAV_RECEIVE];
    }
    delay(5);
    if (sender >= 10)
    {

      NavigationBoard.ToSend(MACRO_SUB_COMMAND_NAV_SEND , 0);
      NavigationBoard.ToSend(MACRO_COMMAND_NAV_SEND     , 0);
      NavigationBoard.ToSend(MACRO_STOP_NAV_SEND, 1);
      NavigationBoard.sendData(NAVIGATION_ADDRESS);
      sender = 0;
    }
    else
      sender += 1;
  }

}














