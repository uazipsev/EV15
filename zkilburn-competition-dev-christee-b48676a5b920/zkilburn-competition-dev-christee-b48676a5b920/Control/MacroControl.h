
inline void macroUpdate()
{
  //Robot says its Done with macro and control box needs to finish the macro
  if (macro_complete == 1 && internalMacroKeeper != 0)
  {

    //internal systems reset
    internalMacroKeeper = 0;
    internalSubKeeper = 0;
    //tell the robot we are done as well   
    sendDataNavigation(0, 0, 0);
    //Make sure the robot gets the update that we are done as well
    ensureReceived(Ending);
    //RESET THE TRACKING VARIABLE
    macro_complete = 0;
    commTimer.resetTimer();
  }
  //---------------------------------------------------------------------
  //FROM THE SCREEN -- MACRO PRESENT
  if (macro_command_screen != 0 && internalMacroKeeper == 0)
  {

    //Change control board state to macro state
    //let it know which macro
    internalMacroKeeper = macro_command_screen;
    internalSubKeeper = macro_sub_command;

    //Tell the comm board about the screens command
    sendDataNavigation(macro_command_screen, macro_sub_command, 0);
    ensureReceived(Starting);

    //erase the data from the screen
    macro_command_screen = 0;
    macro_sub_command = 0;
  }
  if (digitalReadFast(MACRO_BUTTON) == HIGH)
  {
    killMacro();
  }
}


inline void ensureReceived(bool STARTING)
{
  //give it a second to try to recieve the first time reset the resend counter
  delay(5);
  sender = 0;
  //check and store for any valid packet
  if (robot.receiveData())
  {
    //if good checksum, store data locally.
    commMacro = roboMessage[MACRO_COMMAND_RECEIVE];
    macro_complete = roboMessage[MACRO_COMPLETE];
  }

  //Starting a Macro technically doesnt exist
  if (STARTING)
  {   
    //while the robot has not gotten the command
    while (commMacro != internalMacroKeeper)
    {
      //update the information from the robot
      if (robot.receiveData())
      {
        //if good checksum, store data locally.
        commMacro = roboMessage[MACRO_COMMAND_RECEIVE];
      }
      //count how many times we have checked
      sender += 1;
      delay(5);
      //if we checked 5 times with out a change, resend data
      if (sender >= 50)
      {               
        sendDataNavigation(macro_command_screen, macro_sub_command, 0);
        delay(15);
        //reset the timer
        sender = 0;
      }
    }    
  }
  //If you are ending a macro
  else
  {    
    //ROBOT KILLS MACRO
    //The robot says we are done, we are finishing on our side to validate state change
    if (macro_complete == 1)
    {

      //while the robot has not gotten word back from us
      while (macro_complete != 0)
      {
        //update the information from the robot
        if (robot.receiveData())
        {
          //if good checksum, store data locally.
          macro_complete = roboMessage[MACRO_COMPLETE];
        }
        //count how many times we have checked
        sender += 1;
        delay(5);
        //if we checked 5 times with out a change, resend data
        if ((int)sender >= 50)
        {

          sendDataNavigation(0, 0, 1);
          delay(15);
          //reset the timer
          sender = 0;
        }
      }
    }
    else
    {
      //CONTROL BOX KILLS MACRO
      //while the robot has not gotten the command
      while (commMacro != internalMacroKeeper )
      {
        //update the information from the robot
        if (robot.receiveData())
        {
        commMacro = roboMessage[MACRO_COMMAND_RECEIVE];
        }
        //count how many times we have checked
        sender += 1;
        delay(5);
        //if we checked 5 times with out a change, resend data
        if ((int)sender >= 50)
        {            
          sendDataNavigation(0, 0, 1);
          //reset the timer
          sender = 0;
        }
      }
    }

  }
}













