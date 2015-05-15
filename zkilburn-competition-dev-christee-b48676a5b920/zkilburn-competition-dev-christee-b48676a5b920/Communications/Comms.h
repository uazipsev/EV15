//comms.h



// initialize comms

void initializeCommunications() 
{
  //pin mode for comm select
  pinMode(commSelect0, OUTPUT);
  pinMode(commSelect1, OUTPUT);
  selectCommLines(LEDcomm);
  delay(15);
  //Navigation Connection
  Serial.begin(57600);
  //LED 2/ WDT 1/ PIC 3/ DEBUG 0
  Serial2.begin(38400);
  //Lantronix Connection
  Serial1.begin(115200);
  //Motor/Power connection
  //Serial3.begin(57600);
  led.state = 0;
  ControlBoard.begin(Details(controlReceive), COMMUNICATIONS_ADDRESS, false, &Serial1);
  NavigationBoard.begin(Details(navigationReceive), COMMUNICATIONS_ADDRESS, false, &Serial);
  //to_Nav.begin(details(toNav), &Serial);
  //from_Nav.begin(details(fromNav), &Serial);
  to_LED.begin(details(led), &Serial2);
  delay(5);
  packetWait();
  delay(5);
  led.state = MANUAL;
  to_LED.sendData();
}


inline void updateComms() 
{  
  if (LEDtimer.timerDone())
  {
     to_LED.sendData();
  }
  // ---------------RECEIVE COMMS------------------
  //if you hear from the NAVIGATION board
  if (NavigationBoard.receiveData()) 
  {
    //store values that we want to know
    macro_complete    = navigationReceive[MACRO_COMPLETE_NAV_RECEIVE];
    navMacro          = navigationReceive[MACRO_COMMAND_NAV_RECEIVE];
    macro_sub_command = navigationReceive[MACRO_SUB_COMMAND_NAV_RECEIVE];
    
    digitalWrite(13, !digitalRead(13));
    //update the information to send to the CONTROL board
  }

  //if you heard from the CONTROL board
  if (ControlBoard.receiveData())
  {
    if(controlReceive[LED_UPDATE_INDICATOR_CONTROL_RECEIVE])
    {
       static int storedState;
       if(controlReceive[LED_STATE_OVERRIDE_CONTROL_RECEIVE]!=0)
       {
         storedState=led.state;
         led.state=controlReceive[LED_STATE_OVERRIDE_CONTROL_RECEIVE];
       }       
       else 
       {
         led.state=MANUAL;
       }       
     
        led.color=controlReceive[COLOR_PICKER_CONTROL_RECEIVE];
        controlReceive[LED_UPDATE_INDICATOR_CONTROL_RECEIVE]=0;
    }
    //receive information      
    macro_command           = controlReceive[MACRO_COMMAND_CONTROL_RECEIVE];
    macro_sub_command       = controlReceive[MACRO_SUB_COMMAND_CONTROL_RECEIVE];
    controlStop             = controlReceive[MACRO_STOP_CONTROL_RECEIVE];

   
    //update the information to send to the CONTROL board
    ControlBoard.ToSend(AMPS_CONTROL_SEND          , navigationReceive[AMPS_NAV_RECEIVE]);
    ControlBoard.ToSend(AMPHOUR_CONTROL_SEND       , navigationReceive[AMPHOUR_NAV_RECEIVE]);
    ControlBoard.ToSend(VOLTS_CONTROL_SEND         , navigationReceive[VOLTS_NAV_RECEIVE]);
    ControlBoard.ToSend(ENCODERRIGHT_CONTROL_SEND  , navigationReceive[ENCODERRIGHT_NAV_RECEIVE]);
    ControlBoard.ToSend(ENCODERLEFT_CONTROL_SEND   , navigationReceive[ENCODERLEFT_NAV_RECEIVE]);
    ControlBoard.ToSend(ENCODERSPEEDR_CONTROL_SEND , navigationReceive[ENCODERSPEEDR_NAV_RECEIVE]);
    ControlBoard.ToSend(ENCODERSPEEDL_CONTROL_SEND , navigationReceive[ENCODERSPEEDL_NAV_RECEIVE]);
    ControlBoard.ToSend(RIGHT_MOTOR_CONTROL_SEND   , navigationReceive[RIGHT_MOTOR_NAV_RECEIVE]);
    ControlBoard.ToSend(LEFT_MOTOR_CONTROL_SEND    , navigationReceive[LEFT_MOTOR_NAV_RECEIVE]);
    ControlBoard.ToSend(GYRO_CONTROL_SEND          , navigationReceive[GYRO_NAV_RECEIVE]);
    ControlBoard.ToSend(MACRO_COMPLETE_CONTROL_SEND, 0);
    ControlBoard.ToSend(MACRO_COMMAND_CONTROL_SEND , macro_command);
    ControlBoard.sendData(CONTROL_ADDRESS);
    //as long as we are NOT doing a macro request
    if (macro_command == 0)
    {
      NavigationBoard.ToSend(LEFTMOTORSPEED_NAV_SEND, controlReceive[LEFTMOTORSPEED_CONTROL_RECEIVE]);
      NavigationBoard.ToSend(RIGHTMOTORSPEED_NAV_SEND, controlReceive[RIGHTMOTORSPEED_CONTROL_RECEIVE]);
      NavigationBoard.ToSend(ACTUATOR_NAV_SEND, controlReceive[ACTUATOR_CONTROL_RECEIVE]);
    }
    else
    {    
//      Serial2.print("Macro_command: ");
//      Serial2.println(macro_command);
//      Serial2.print("Macro_sub_command: ");
//      Serial2.println(macro_sub_command);
     led.state = MACRO;
      //doing a macro request
      macroUpdate();
    }
    //Reset the safety timer and the resend timer, mark we heard stuff
    commTimer.resetTimer(); 
    //prepare information from the CONTROL board for the NAVIGATION
    NavigationBoard.ToSend(MACRO_COMMAND_NAV_SEND     , macro_command);
    NavigationBoard.ToSend(MACRO_SUB_COMMAND_NAV_SEND , macro_sub_command);
    NavigationBoard.ToSend(MACRO_STOP_NAV_SEND        , controlStop);      
    NavigationBoard.sendData(NAVIGATION_ADDRESS);
  }
  //failed to get fresh packet
  else  
  {
    commSafety();
  }
}

inline void commSafety()
{
  commTimer.updateTimer();

  if (commTimer.timerDone())
  {
    delay(5);
    led.state = COMMAquire;
    to_LED.sendData();   
    packetWait();
    delay(50);
    led.state = MANUAL;
    to_LED.sendData();
  }
}

void selectCommLines(int comm)
{
  switch (comm)
  {
  case DEBUGcomm:
    digitalWrite(commSelect0, LOW);
    digitalWrite(commSelect1, LOW);
    break;
  case WDTcomm:
    digitalWrite(commSelect0, HIGH);
    digitalWrite(commSelect1, LOW);
    break;
  case PICcomm:
    digitalWrite(commSelect0, HIGH);
    digitalWrite(commSelect1, HIGH);
    break;
  case LEDcomm:
  delayMicroseconds(50);
    digitalWrite(commSelect0, LOW);
    digitalWrite(commSelect1, HIGH);
  delayMicroseconds(50);
    break;
  }
}


void packetWait() 
{
  //may cause issues sending this data to the navigation when the system is not listening for a response or handing a few cases.

  //maybe we store these values before erasing them to resume after comms loss?
  NavigationBoard.ToSend(MACRO_COMMAND_NAV_SEND     , 0);
  NavigationBoard.ToSend(MACRO_SUB_COMMAND_NAV_SEND , 0);
  NavigationBoard.ToSend(MACRO_STOP_NAV_SEND        , 1);
  NavigationBoard.ToSend(LEFTMOTORSPEED_NAV_SEND    , 0);
  NavigationBoard.ToSend(RIGHTMOTORSPEED_NAV_SEND   , 0);
  NavigationBoard.ToSend(ACTUATOR_NAV_SEND          , 255);
  NavigationBoard.sendData(NAVIGATION_ADDRESS);
  // set init mode
  delay(5);
  led.state = COMMAquire;
  to_LED.sendData();

  sendTime.resetTimer();
  while (!ControlBoard.receiveData()) 
  {
//    static Timers DebugTimer(250);
//    if(DebugTimer.timerDone()){
//      selectCommLines(DEBUGcomm);
//      Serial2.println("WAITING FOR PACKET");
//      selectCommLines(LEDcomm);
//    }
    delay(5);
  }
  led.state = MANUAL;
  to_LED.sendData();
  commTimer.resetTimer(); //safety system reset
  NavigationBoard.sendData(NAVIGATION_ADDRESS);
}













