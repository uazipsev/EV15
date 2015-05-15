[quote]
[color = #7E7E7E] //static Timers verboseTime(500);[/color]
[color = #7E7E7E] //  verboseTime.updateTimer();[/color]
[color = #7E7E7E] //  [/color]

[ / quote]

//int weighted[20];
//int weightedSensorReading(int weight, int reading) {
//
//
//}
//bool getSideChange(bool Right){
//  if (Right)
//    sideLength=rightS;
//  else
//    sideLength=leftS;
//  while(lastMeasuredDistance!=sideLength) {
//    lastMeasuredDistance=weightedSensorReading(1,Right);
//  }
//
//  slope=lastMeasuredDistance-sideLength;
//  if(slope>0)
//    return POSITIVE;
//  else
//    return NEGATIVE;
//}


inline bool dDrive(int offset)
{
  sendTimer.updateTimer();
  if (sendTimer.timerDone()) //&& !readyToSend)
  {
    outMotor.leftMotorSpeed = 15;
    outMotor.rightMotorSpeed = 15;
    to_motor.sendData();

    if (from_PIC.receiveData()) {
      //Pull data
      IRLF = PIC.LongFront;
      IRSFL = PIC.MediumFrontLeft;
      IRSFR = PIC.MediumFrontRight;
      IRLB = PIC.LongBack;
      IRMB = PIC.MediumBack;
      IRSBL = PIC.ShortLeft;
      IRSBR = PIC.ShortRight;
      IRLL = PIC.LongLeft;
      IRML = PIC.MediumLeft;
      IRLR = PIC.LongRignt;
      IRMR = PIC.MediumRight;

      //Forward Data
      Nav.LongFront = IRLF;
      Nav.MediumFrontLeft = IRSFL;
      Nav.MediumFrontRight = IRSFR;
      Nav.LongBack = IRLB;
      Nav.MediumBack = IRMB;
      Nav.ShortLeft = IRSBL;
      Nav.ShortRight = IRSBR;
      Nav.LongLeft = IRLL;
      Nav.MediumLeft = IRML;
      Nav.LongRight = IRLR;
      Nav.MediumRight = IRMR;
      //Thesee suck to type...
    }
    if (from_comm.receiveData()) {

      if ((macro_command != Comm.macro_command) || (Comm.macro_stop == 1)) {
        macro_command = 0;
        macro_sub_command = 0;
        macro_stop = 1;
        delay(5);
        Serial1.flush();
        break;
      }
    }
  }
  linkTimer.updateTimer();
  if (linkTimer.timerDone()) {
    to_comm.sendData();
  }








  continueMacro = 0;

  //grab the magnitude of the drive
  //(the sign says direction)
  int duration = 6;

  //create time keeping variables
  int timeNow = millis();
  int timeFinish = timeNow + (duration * 200);

  //drive while time not reached
  while ((timeNow < timeFinish) && (continueMacro == 0))
  {
    if (from_control.receiveData())
    {
      updateScreen();
      continueMacro = fromControl.macro_stop;
    }
    differentialDrive(20, -offset * 1.5);
    to_motor.sendData();
    timeNow = millis();
  }
  //stop the robot after
  allStop();
  motor_unStick();
}


inline bool followRight(int target, int rangeFront) {
  continueMacro = 0;
  int magnitude;
  int outputSide;
  int travelDistanceRemaining = frontS - rangeFront;

  PID sideError(target, sideKpR, sideKiR, sideKdR, 0);
  sideError.clearSystem();
  PIDTimer.resetTimer();
  while ((frontS >= rangeFront) && continueMacro == 0)  {
    updateGyro();
    updateSensorBoard();                //Get new data in from sensor board
    updateIRSensors();                     //update IR equations for new values

      PIDTimer.updateTimer();
    if (PIDTimer.timerDone()) {
      outputSide = sideError.updateOutput(rightS);                  //calculate command for turning
      travelDistanceRemaining = ( frontS - rangeFront );

      if (travelDistanceRemaining > slowingDistance)
        magnitude = motorHigh;
      else
        magnitude = motorHigh - (travelDistanceRemaining / slowingDistance) * motorHigh; //calculate speed forward

      if (!(varIsAbout(target, rightS, sideDeadR)) && abs(macroAngle < gyroCorrectR))    //if you have skewd off course
        differentialDrive(magnitude, outputSide);                                         //correct if gyro doesnt say we are over correcting
      else if (abs(macroAngle) > gyroCorrectR)
        turn(-macroAngle);
      else     //else turn back
      variableDrive(constrain(magnitude, motorLow, motorHigh));

      //send motor data
      to_motor.sendData();
      if (from_control.receiveData()) {
        //report to the screen with pid data
        updateScreen(sideError);
        //check for command halt
        continueMacro = fromControl.macro_stop;
      }
    }
  }
  //end command
  allStop();
  motor_unStick();

  //return if halt
  return (continueMacro == 0);
}
//-----------------------------------------------------------------------------------
inline bool followLeft(int rangeSide, int rangeFront)
{
  //record the initial sensor used to perform target management

    continueMacro = 0;
  int magnitude;
  int outputSide;
  int travelDistanceRemaining = frontS - rangeFront;
  PID sideError(rangeSide, sideKpL, sideKiL, sideKdL, 0);
  sideError.clearSystem();
  PIDTimer.resetTimer();
  while ((frontS >= rangeFront) && continueMacro == 0)  {
    //update all readings before we make decisions (some are throttled in the background with timers)
    updateGyro();
    updateSensorBoard();
    updateIRSensors();


    //update the PID system timer
    PIDTimer.updateTimer();
    if (PIDTimer.timerDone())  //Check if the timer is done
    {
      //calculate the amount of travel forward left and set up speed control
      magnitude = constrain((frontS - rangeFront), motorLow, motorHigh);
      outputSide = (sideError.updateOutput(leftS)); //if timer is done make a PID decision

      if (!(varIsAbout(rangeSide, leftS, sideDeadL)) && abs(macroAngle < gyroCorrectL))
        differentialDrive(magnitude, outputSide);
      else if (abs(macroAngle > gyroCorrectL))
        differentialDrive(magnitude, -outputSide);
      else
      {
        variableDrive(magnitude);
        sideError.clearIntegral();
      }
      //send motor data
      to_motor.sendData();
      if (from_control.receiveData()) {
        //report to the screen
        updateScreen(sideError);
        //check for halt command
        continueMacro = fromControl.macro_stop;
      }
    }
  }
  //end command
  allStop();
  motor_unStick();

  //return if halt
  return (continueMacro == 0);
}

