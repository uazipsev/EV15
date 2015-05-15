//------------------------------------------------------------------
bool writeUptime()
{
  if (CTS)
  {
    if (uptime > 9999)
    {
      uptime = 0;
    }
    Seconds.updateTimer();
    if (Seconds.timerDone()) {
      writeObject(LEDDIGITS, 0, uptime++);
      Seconds.resetTimer();
      return true;
    }
    else return false;
  }
  else  return false;
}


void writeScreen() {
  //screenTimer.updateTimer();
  if (CTS)
    if (screenTimer.timerDone())
    {

      //if we are updating the screen during a macro and the page isnt the macro active page
      //    if ((internalMacroKeeper != 0))
      //    {
      //      pageKeeper = activePage;  //record which page is active (to return to after macro)
      //      writeObject(FORMMESSAGE, MACROACTIVE, 0);    //change the page to the active macro page
      //      activePage = MACROACTIVE;
      //    }

      //figure out which page is displayed and
      //display only what you  need to

      static byte counter;
      static bool flop = true;
      //      static Timers PIDSendTiming(25);
      //
      //      if((!flop)&&PIDSendTiming.timerDone())  flop=true;
      //
      //      if((internalMacroKeeper!=0)&&flop)
      //      {
      //        static bool flip=false;
      //        //When macroing logg data to screen even if your not watching it
      //        if(flip)
      //        {
      //          writeObject(SCOPE, 0, motorR);   //R
      //          flip=false;
      //          flop=false;
      //          PIDSendTiming.resetTimer();
      //        }
      //        else
      //        {
      //          writeObject(SCOPE, 0, motorL);   //L
      //          flip=true;
      //        }
      //      }
      //      else
      if (writeUptime()) {
      }
      else
        switch (activePage)
        {
          case StartPage:

            //writeObject(LEDDIGITS, 0, counter);
            switch (counter) {
              case 1:
                break;
              case 2:
                writeObject(ANGULARMETER, 0, constrain(((volts / 10.0) - 240), 0, 40)); //BATTERY METER
                break;
              case 3:
                writeObject(LEDDIGITS, 5, (uint16_t)encoderL);         //Left Encoder
                break;
              case 4:
                writeObject(LEDDIGITS, 6, (uint16_t)encoderR);         //Right encoder
                break;
              case 5:
                writeObject(LEDDIGITS, 12, encoderSpeedR);         //Right encoder
                break;
              case 6:
                writeObject(LEDDIGITS, 11, encoderSpeedL);        //Right encoder
                break;
              case 7:
                writeObject(LEDDIGITS, 9, constrain(abs(milliamps) / 10.0, 0, 9999));       //amp readout
                counter = 0;
                break;
              default:
                counter = 0;
            }
            counter++;
            break;
          case Battery:
            switch (counter)
            {
              case 1:
                writeObject(ANGULARMETER, 1, constrain(((volts / 10.0) - 240), 0, 40));
                break;
              case 2:
                writeObject(ANGULARMETER, 3,  constrain(((2000 - (milliamphours / 10.0)) / 10.0), 0, 200));
                break;
              case 3:
                writeObject(GUAGE, 0, (abs(milliamps) / 500.0)  );
                break;
              case 4:
                writeObject(LEDDIGITS, 4, constrain((abs(milliamps) / 100.0), 0, 9999));
                break;
              case 5:
                writeObject(LEDDIGITS, 19, abs(milliamphours / 100.0));
                counter = 0;
                break;
              default:
                counter = 0;
            }
            counter++;
            //BACKUP L
            break;
          case Info:
            break;
          case Manual:
            switch (counter)
            {

              case 1:
                writeObject(ANGULARMETER, 2, constrain(((volts / 10.0) - 240), 0, 40));
                break;
              case 2:
                writeObject(COOLGAUGE, 0, encoderSpeedL);            //Left Speed (0-200)
                break;
              case 3:
                writeObject(COOLGAUGE, 1,   encoderSpeedR);           //Right Speed (0-200)
                counter = 0;
                break;
              default:
                counter = 0;
            }
            counter++;

            break;
          case CommError:
            counter = 0;
            break;
          case Autonomous:
            switch (counter)
            {
              case 1:

                counter = 0;
                break;
              default:
                counter = 0;
            }
            counter++;
            break;
          case Debug:

            break;
          case ActuatorMacros:
            switch (counter)
            {
              case 1:
                writeObject(LEDDIGITS   , 31, setAngle);
                break;
              case 2:
                writeObject(ANGULARMETER, 4, bucketAngle);
                counter = 0;
                break;
              default:
                counter = 0;
            }
            counter++;
            break;
          case MacroTester:
            switch (counter)
            {
              case 1:
                writeObject(LEDDIGITS, 14, encoderL);   //L
                break;
              case 2:
                writeObject(LEDDIGITS, 20, encoderR);   //R
                break;
              case 3:
                writeObject(LEDDIGITS, 23, encoderSpeedL);   //L
                break;
              case 4:
                writeObject(LEDDIGITS, 24, encoderSpeedR);   //R
                break;
              case 5:
                writeObject(LEDDIGITS, 21, abs(motorL));   //L
                break;
              case 6:
                writeObject(LEDDIGITS, 22, abs(motorR));   //R
                break;
              case 7:
                writeObject(LEDDIGITS, 25, abs(gyroAngle));   //R
                counter = 0;
                break;
              default:
                counter = 0;
            }
            counter++;
            break;
          case PID:
            switch (counter % 10)
            {
              case 1:
                if (internalMacroKeeper == 0) {
                  writeObject(SCOPE, 0, motorR);   //R
                }
                break;
              case 2:
                if (internalMacroKeeper == 0) {
                  writeObject(SCOPE, 0, motorL);   //L
                }
                break;

              case 3:
                writeObject(LEDDIGITS, 15, abs(motorL));   //L
                break;
              case 4:
                writeObject(LEDDIGITS, 16, abs(motorR));   //R
                counter = counter + 4;
                break;
              case 9:
                if (counter > 120) {
                  writeObject(FORMMESSAGE, PID, 0);
                  counter = 0;
                }
                break;
            }
            counter++;
            break;
          case PIDViewer:
            switch (counter)
            {
              case 1:
                if (internalMacroKeeper == 0) {
                  writeObject(SCOPE, 1, errorMargin);
                }
                break;
              case 2:
                if (internalMacroKeeper == 0) {
                  writeObject(SCOPE, 2, derivative);
                }
                break;
              case 3:
                if (internalMacroKeeper == 0) {
                  writeObject(SCOPE, 3, integral);
                }

                break;
              default:
                counter = 0;
            }
            counter++;
            break;
          case GyroViewer:
            switch (counter)
            {
              case 1:
                writeObject(SCOPE, 4, constrain(gyroAngle, -180, 180));
                break;
              default:
                counter = 0;
            }
            counter++;
            break;
          case EncoderMacros:
            switch (counter)
            {
              case 1:
                writeObject(LEDDIGITS, 26, abs(encoderValue));
                break;
              case 2:
                writeObject(USERLED, 2, (encoderValue < 0));
                break;
              case 3:
                writeObject(LEDDIGITS, 27, (uint16_t)encoderL);         //Left Encoder
                break;
              case 4:
                writeObject(LEDDIGITS, 28, (uint16_t)encoderR);         //Right encoder
                break;
              case 5:
                writeObject(LEDDIGITS, 29, encoderSpeedR);         //Right encoder
                break;
              case 6:
                writeObject(LEDDIGITS, 30, encoderSpeedL);        //Right encoder
                counter = 0;
                break;
              default:
                counter = 0;
            }
            counter++;
            break;
          case MacroPage:
            counter = 0;
            break;
          case WiiPage:
            switch (counter)
            {
              case 1:
                writeObject(LEDDIGITS, 32, leftAngle);
                break;
              case 2:
                writeObject(LEDDIGITS, 33, rightAngle);
                counter=0;
                break;
              default:
                counter = 0;
            }
            counter++;
            break;
          default:
            break;
        }
      screenTimer.resetTimer();
    }
}












