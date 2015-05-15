//screen.h
//Zac Kilburn
//3-8-14

//Screen.h handles all of the screens input and output systems.
//finally have an extremely stable version of this code for comms
//


//the protocol is as follows
//byte #         0             1            2       3    4    5
//           [command #] [typeOfEntity] [Entity#] [dH]  [dL] [CRC]
// byte 0 ---- 0x07 is a command output from screen
// byte 1 ---- entity type is a button or slider etc.
// byte 2 ---- which button slider etc was pressed
// byte 3/4 -- the data values involved (used for sliders not buttons)
// byte 5 ---- cyclic redundancy check (simple xor with each byte)

inline static bool readStream()
{
  //while bytes are still there
  while (Serial3.available())
  {
    //the the leading byte is not a 0x07 (what we need)
    if (Serial3.peek() != 0x07)
    {
      //eat it out and check again
      Serial3.read();
      CTS = true;
    }
    else
    {
      //else get outta here (its a 0x07)
      break;
    }
  }
  //if there are at least our 6 byte packet in the stream
  if (Serial3.peek() == 0x07)
  {
    if (Serial3.available() > 5)
    {
      CTS = true;
      // get the all 6 of the bytes in the packet
      receivedPack[0] = Serial3.read();
      //calculating the checksum as we go
      checksum  = receivedPack[0];
      receivedPack[1] = Serial3.read();
      checksum ^= receivedPack[1];
      receivedPack[2] = Serial3.read();
      checksum ^= receivedPack[2];
      receivedPack[3] = Serial3.read();
      checksum ^= receivedPack[3];
      receivedPack[4] = Serial3.read();
      checksum ^= receivedPack[4];
      receivedPack[5] = Serial3.read();
      checksum ^= receivedPack[5];
      return true;
    }
    else
      return false;
  }
  else
    return false;
}

//---------------------------------------------------------------------
inline static bool writeObject(byte object, byte index, unsigned int data)
{

  byte lsb = (data >> 0) & 0xFF;
  byte msb = (data >> 8) & 0xFF;
  byte checksum = 0;
  if (CTS)
  {
    Serial3.write(0x01);
    checksum  = 0x01;
    //delayMicroseconds(150);
    Serial3.write(object);
    checksum ^= object;
    //delayMicroseconds(150);
    Serial3.write(index);
    checksum ^= index;
    //delayMicroseconds(150);
    Serial3.write(msb);
    checksum ^= msb;
    //delayMicroseconds(150);
    Serial3.write(lsb);
    checksum ^= lsb;
    //delayMicroseconds(150);
    Serial3.write(checksum);
    CTS = false;
  }

}




//---------------------------------------------------------------------
//this function updates the screen (externally called)
void updateScreen()
{
  readObject();
  writeScreen();
}
//---------------------------------------------------------------------
//Check for Serial3 available--
//if packet is present, parse it and instruct robot accordingly
int colorForLED;
int angle_Wii = 0;
int beacon_Wii = 0;
int camera_Wii = 0;
inline static bool readObject()
{
  //Erase the old pack before parsing
  for (int i = 0; i < 6; i++)
  {
    receivedPack[i] = 0;
  }
  //check to see if a packet persists in memory
  // Compare byte 1 to check for CMD Message
  if (readStream())
    if (receivedPack[0] == 0x07)
    {
      CTS = true;
      //store the data as a word (not a byte)
      unsigned int dataIn = ((0x00FF & receivedPack[3]) << 8) | (0x00FF & receivedPack[4]);
      switch (receivedPack[1])
      {
        case COLORPICKER:
          if (receivedPack[2] == 0)
          {
            colorForLED = dataIn;
            robot.ToSend(LED_STATE_OVERRIDE, COLOR_OVERRIDE);
            robot.ToSend(COLOR_PICKER, dataIn);
            robot.ToSend(LED_UPDATE_FLAG, 1);
            robot.sendData(LED_ADDRESS);
            delay(7);
          }
        case FORMMESSAGE:
          activePage = receivedPack[2];
          break;
          //if byte 2 is a button
        case BUTTON:
          //check to see which button
          switch (receivedPack[2])
          {
            case 25:  //DUMP

              macro_command_screen = ACTUATOR_SNIPPIT;
              macro_sub_command = 254;
              break;
            case 26:  //SET ANGLE

              macro_command_screen = ACTUATOR_SNIPPIT;
              macro_sub_command = setAngle;
              break;
            case 27:   //DIG

              macro_command_screen = ACTUATOR_SNIPPIT;
              macro_sub_command = 253;
              break;
            case 28:   //VIBRATE

              break;

              //AUTO TEST
            case 15:
              macro_command_screen = 1;
              macro_sub_command = 1;
              break;
            case 8:
              printerPrint();
              break;
            case 32:
              static bool leftRight = true;
              if (leftRight) {
                macro_command_screen = 2;
                macro_sub_command = 1;
                leftRight = false;
              }
              else {
                macro_command_screen = 3;
                macro_sub_command = 1;
                leftRight = true;
              }
              break;
              //Stop message
            case 23:
              killMacro();
              break;
              //P1
            case 35:
              macro_command_screen = MACRO_SNIPPIT;
              macro_sub_command = 1;
              break;
              //P2
            case 36:
              macro_command_screen = MACRO_SNIPPIT;
              macro_sub_command = 2;
              break;
              //P3
            case 37:
              macro_command_screen = MACRO_SNIPPIT;
              macro_sub_command = 3;
              break;
              //P4
            case 38:
              macro_command_screen = MACRO_SNIPPIT;
              macro_sub_command = 4;
              break;
              //P5
            case 39:
              macro_command_screen = MACRO_SNIPPIT;
              macro_sub_command = 5;
              break;

            case 40:
              macro_command_screen = 5;
              macro_sub_command = 1;
              break;
            case 45:
              sendLEDdata(0, 0);
              break;
            case 46:
              //STOBE
              sendLEDdata(STROBE, colorForLED);
              break;
            case 47:
              //POLICE
              sendLEDdata(POLICE, 0);
              break;
            case 48:
              //RAINBOW
              sendLEDdata(RAINBOW, 0);
              break;
            case 49:
              //PARTY
              sendLEDdata(PARTY, 0);
              break;
            case 50:
              //UA
              sendLEDdata(3, 0);
              break;
            case 51:
              //CHRISTMAS
              sendLEDdata(CHRISTMAS, 0);
              break;
            case 54:
              macro_command_screen = ENCODER_SNIPPIT;
              macro_sub_command = 25;
              break;
            case 55:
              macro_command_screen = ENCODER_SNIPPIT;
              macro_sub_command = 50;
              break;
            case 56:
              macro_command_screen = ENCODER_SNIPPIT;
              macro_sub_command = 75;
              break;
            case 57:
              macro_command_screen = ENCODER_SNIPPIT;
              macro_sub_command = 100;
              break;
            case 58:
              macro_command_screen = ENCODER_SNIPPIT;
              macro_sub_command = 200;
              break;
            case 59:
              macro_command_screen = ENCODER_SNIPPIT;
              macro_sub_command = 500;
              break;
            case 60:
              macro_command_screen = ENCODER_SNIPPIT;
              macro_sub_command = -25;
              break;
            case 61:
              macro_command_screen = ENCODER_SNIPPIT;
              macro_sub_command = -50;
              break;
            case 62:
              macro_command_screen = ENCODER_SNIPPIT;
              macro_sub_command = -75;
              break;
            case 63:
              macro_command_screen = ENCODER_SNIPPIT;
              macro_sub_command = -100;
              break;
            case 64:
              macro_command_screen = ENCODER_SNIPPIT;
              macro_sub_command = -200;
              break;
            case 65:
              macro_command_screen = ENCODER_SNIPPIT;
              macro_sub_command = -500;
              break;
              //MACRO PAGE SNIPPITS
            case 66:
              macro_command_screen = MACRO_SNIPPIT;
              macro_sub_command = 6;
              break;
            case 67:
              macro_command_screen = MACRO_SNIPPIT;
              macro_sub_command = 7;
              break;
            case 68:
              macro_command_screen = MACRO_SNIPPIT;
              macro_sub_command = 8;
              break;
            case 69:
              macro_command_screen = MACRO_SNIPPIT;
              macro_sub_command = 9;
              break;
            case 70:
              macro_command_screen = MACRO_SNIPPIT;
              macro_sub_command = 10;
              break;
            case 71:
              macro_command_screen = MACRO_SNIPPIT;
              macro_sub_command = 11;
              break;
            case 72:
              macro_command_screen = MACRO_SNIPPIT;
              macro_sub_command = 12;
              break;
            case 73:
              macro_command_screen = MACRO_SNIPPIT;
              macro_sub_command = 13;
              break;
            case 74:
              macro_command_screen = MACRO_SNIPPIT;
              macro_sub_command = 14;
              break;
            case 75:
              macro_command_screen = MACRO_SNIPPIT;
              macro_sub_command = 15;
              break;
            case 17:
              macro_command_screen = WII_SNIPPIT + beacon_Wii;
              macro_sub_command = (camera_Wii * 180) + angle_Wii;
              break;
            case 78:    //LOCALIZE
              macro_command_screen = MACRO_SNIPPIT;
              macro_sub_command = 4;
              break;
            case 79:  //CONTINOUS
              robot.ToSend(WII_SUBSYSTEM_MODE, 4);
              robot.sendData(PIC_ADDRESS);
              break;
            case 80: //Do HORIZONTAL
              robot.ToSend(WII_SUBSYSTEM_MODE, 2);
              robot.sendData(PIC_ADDRESS);
              break;
            case 81: //VERTICAL
              robot.ToSend(WII_SUBSYSTEM_MODE, 1);
              robot.sendData(PIC_ADDRESS);
              break;
              case 82: //left side assumption
              
              macro_command_screen = MACRO_SNIPPIT;
              macro_sub_command = 5;
              break;
          }
          break;
          //slider update
        case SLIDER:
          //check to see which slider
          switch (receivedPack[2])
          {
            case 0:
              setAngle = dataIn;
              break;
            case 1:
              encoderValue = (constrain(dataIn, 0, 100) - 50.0) * 10.0;
              break;
          }
          break;
          //received is a knob
        case KNOB:
          angle_Wii = dataIn;
          break;
          //else update the form that is currently up
        case FOURDBUTTON:
          switch (receivedPack[2])
          {
            case 0:
              camera_Wii = dataIn;
              break;
            case 1:
              beacon_Wii = dataIn;
              break;
          }
          break;
        case KEYBOARD:
          
          break;
      }
    }
}



inline int calcOutputHeading(int in)
{
  if (outputHeading <= 360 && outputHeading >= 0)
  {
  }
  //else condition the output
  else
  {
    while (outputHeading < 0)
    {
      outputHeading += 360;
    }
    while (outputHeading > 360)
    {
      outputHeading -= 360;
    }
  }
  outputHeading = 360 - outputHeading;
  return outputHeading;
}

inline int calcAndConstrainHeading(int calcHeading)
{
  while (calcHeading < 0)
  {
    calcHeading += 360;
  }
  while (calcHeading > 360)
  {
  }
  calcHeading = 360 - calcHeading;
  int offset = angle_command - calcHeading;
  while (offset > 360)
  {
    offset -= 360;
  }
  while (offset < -360)
  {
    offset += 360;
  }
  if (abs(offset) > 180)
  {
    if (offset > 0)
    {
      offset = offset - 360;
    }
    else if (offset < 0)
    {
      offset = offset + 360;
    }
  }
  return offset;
}












