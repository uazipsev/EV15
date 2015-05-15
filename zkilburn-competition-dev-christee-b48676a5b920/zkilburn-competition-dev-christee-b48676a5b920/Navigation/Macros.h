//macros.h
//3-2-14 STACEE can walk in circles (   almost :)  )
//3-25-14 STACEE can do forward/mine/backward/dump

//Macro_commands
#define MACRO_SNIPPIT 4
#define ENCODER_SNIPPIT 6
#define ACTUATOR_SNIPPIT 7


inline void initMacroSystem()
{
  macro_stop = false;
  continuable = true;
  Navigation.ToSend(MACRO_COMMAND_SEND, stored_macro_command);
  Navigation.sendData(CONTROL_ADDRESS);
  //
  //  Navigation.ToSend(MACRO_COMMAND_SEND, stored_macro_command);
  //  Navigation.sendData(CONTROL_ADDRESS);
  //  Navigation.ToSend(MACRO_COMMAND_SEND, stored_macro_command);
  //  Navigation.sendData(CONTROL_ADDRESS);

  if (stored_macro_command == 1)
  {
    while (continuable)
    {
      straightPathMineDump();
    }
  }
  else
  {
    //    Serial.print("Heard Macro: ");
    //    Serial.println(macro_command);
    //    Serial.print("Macro_sub_command: ");
    //    Serial.println(macro_sub_command);
    switch (stored_macro_command)
    {
      case 2:
        runEncoderDistanceEvenly(25);
        break;
      case 3:
        runEncoderDistanceEvenly(-25);
        break;
      case MACRO_SNIPPIT:
        switch (macro_sub_command)
        {
          case 1:
            encoderRun1();
            break;
          case 2:
            encoderRun5();
            break;
          case 3:
            sendActuatorPosition(5);
            break;
          case 4:
            orientWithWii();
            break;
          case 5:
            wiiCameraLocalize(HORIZONTAL_BEACON, 67 , LEFT_CAMERA);
            break;
          case 6:
            fullRoutine();
            break;
          case 7:
            fullDigRoutine();
            break;
          case 8:
            bucketMovementDig();
            break;
          case 9:
            bucketMovementDump();
            break;
          case 10:
            fiftyForwardFiftyBackward();
            break;
          case 11:
            squareRoutine();
            break;
          case 12:
            orientWithWii();
            break;
          case 13:
            doTurn(90);
            break;
          case 14:
            doTurn(-90);
            break;
          case 15:
            runEncoderDistanceEvenly(25);
            break;
        }
        break;
      case 5:
        wipeEncoders();
        initMPUFilters();
        break;
      case ENCODER_SNIPPIT:
        runEncoderDistanceEvenly(macro_sub_command);
        break;
      case 7:
        if (macro_sub_command >= 0 && macro_sub_command <= 90)
          sendActuatorPosition(macro_sub_command);
        else if (macro_sub_command == 254)
          sendActuatorPosition(75);
        else if (macro_sub_command == 253)
          sendActuatorPosition(5);
        break;
      case 8:
        if (macro_sub_command <= 180) 
        {
          wiiCameraLocalize(VERTICAL_BEACON, macro_sub_command, LEFT_CAMERA);
        }
        else
        {
          wiiCameraLocalize(VERTICAL_BEACON, macro_sub_command, RIGHT_CAMERA);
        }
        break;
      case 9:
        if (macro_sub_command <= 180)
        {
          wiiCameraLocalize(HORIZONTAL_BEACON, macro_sub_command - 180, LEFT_CAMERA);
        }
        else
        {
          wiiCameraLocalize(HORIZONTAL_BEACON, macro_sub_command - 180, RIGHT_CAMERA);
        }
        break;
    }
  }
  terminateMacroSystem();
}

inline bool straightPathMineDump()
{

}

inline bool orientWithWii()
{
  //Line up with target
  if (!wiiCameraLocalize(VERTICAL_BEACON, 90, LEFT_CAMERA)) {
    if (wiiCameraLocalize(HORIZONTAL_BEACON, 90, LEFT_CAMERA)) {
      //This means only the horizontal is visible
    }
  }
  else {
    //This means you can see vertical beacon... may also the horizontal
  }



  return macro_stop == 0;
}

void fullRoutine()
{
  while (!macro_stop)
  {
    //Move bucket and drive
    sendActuatorPosition(BUCKET_DRIVE_ANGLE_SET);
    runEncoderDistanceEvenly(TRAVERSE_DRIVE_DISTANCE);
    //Move bucket dig
    sendActuatorPositionDig(BUCKET_DIG_ANGLE_SET);
    //Scoop
    runEncoderDistanceEvenly(DIG_DRIVE_DISTANCE);
    //Toss back
    sendActuatorPosition(BUCKET_DRIVE_ANGLE_SET + 20);
    //Drive Postition
    sendActuatorPosition(BUCKET_DRIVE_ANGLE_SET);
    runEncoderDistanceEvenly(-TRAVERSE_DRIVE_DISTANCE);
    //Dump
    sendActuatorPosition(BUCKET_DUMP_ANGLE_SET);
    delay(DELAY_BUCKET_EMPTY);
    //Back to drive
    sendActuatorPosition(BUCKET_DRIVE_ANGLE_SET);
  }
}


void driveDigDistance()
{
  runEncoderDistanceEvenly(DIG_DRIVE_DISTANCE);
}



void fiftyForwardFiftyBackward()
{
  while (macro_stop != 1)
  {
    runEncoderDistanceEvenly(50);
    runEncoderDistanceEvenly(-50);
  }
}

void squareRoutine()
{
  while (macro_stop != 1)
  {
    runEncoderDistanceEvenly(50);
    doTurn(90);
  }
}

//***********LOW LEVEL ROBOT METHODS (USED INTERNALLY MOSTLY)***********
//Robot motors ALL Stop
inline void allStop()
{
  sendMotorCommand(255, 255, 255);
}
//When motor board recieves 255's it appears to lock up,
// this method assures they are unstuck (as one may assume :) )
inline void motor_unStick()
{
  sendMotorCommand(0, 0, 255);
}

