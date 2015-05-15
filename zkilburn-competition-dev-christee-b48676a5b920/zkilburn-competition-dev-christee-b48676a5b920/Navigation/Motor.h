//Control the motor signal via feedback from the encoders

#define motorKp 1.5
#define motorKi 0
#define motorKd 0

PID motorOutput(0, motorKp, motorKi, motorKd, 2);
PID motorOutputL(0, motorKp, motorKi, motorKd, 2);
PID motorOutputR(0, motorKp, motorKi, motorKd, 2);




void motorOutputControlLeft(int speedRun)
{
  motorOutputL.updateTarget(abs(speedRun));
  int mag;
  if (speedRun > 0)
    mag = constrain(abs(motorOutput.updateOutput(encoderSpeedL)), motorLowForward, motorHighForward);
  else
    mag = constrain(abs(motorOutput.updateOutput(encoderSpeedL)), motorLowBackward, motorHighBackward);

  if (speedRun > 0)
    sendMotorCommand(mag, 0);
  else
    sendMotorCommand(-mag, 0);
}

void motorOutputControlRight(int speedRun)
{
  motorOutputR.updateTarget(abs(speedRun));
  int mag;
  if (speedRun > 0)
    mag = constrain(abs(motorOutput.updateOutput(encoderSpeedR)), motorLowForward, motorHighForward);
  else
    mag = constrain(abs(motorOutput.updateOutput(encoderSpeedR)), motorLowBackward, motorHighBackward);

  if (speedRun > 0)
    sendMotorCommand(0, mag);
  else
    sendMotorCommand(0, -mag);
}



void motorOutputControlCorrect(int speedRun, int eL, int eR)
{
  motorOutput.updateTarget(abs(speedRun));
  int mag;
  if (speedRun > 0)
    mag = constrain(abs(motorOutput.updateOutput((encoderSpeedL + encoderSpeedR) / 2.0)), motorLowForward, motorHighForward);
  else
    mag = constrain(abs(motorOutput.updateOutput((encoderSpeedL + encoderSpeedR) / 2.0)), motorLowBackward, motorHighBackward);
  int magL, magR;
  if (eL > eR)
  {
    magL = mag - 6;
    magR = mag + 2;
  }
  else
  {
    magL = mag + 2;
    magR = mag - 6;
  }

  if (speedRun > 0)
    sendMotorCommand(magL, magR);
  else
    sendMotorCommand(-magL, -magR);
}
//Encoder feedback to control speed
//speed is a positive or negative number representing a control speed
void motorOutputControl(int speedRun)
{
  motorOutput.updateTarget(abs(speedRun));
  int mag;
  if (speedRun > 0)
    mag = constrain(abs(motorOutput.updateOutput((encoderSpeedL + encoderSpeedR) / 2)), motorLowForward, motorHighForward);
  else
    mag = constrain(abs(motorOutput.updateOutput((encoderSpeedL + encoderSpeedR) / 2)), motorLowBackward, motorHighBackward);
  if (speedRun > 0)
    sendMotorCommand(mag, mag);
  else
    sendMotorCommand(-mag, -mag);

}

void motorOutputControlCorrect(int speedRun, int eL, int eR, bool useGyro)
{
  if (!useGyro)
  {
    motorOutput.updateTarget(abs(speedRun));
    int mag;
    if (speedRun > 0)
      mag = constrain(abs(motorOutput.updateOutput((encoderSpeedL + encoderSpeedR) / 2)), motorLowForward, motorHighForward);
    else
      mag = constrain(abs(motorOutput.updateOutput((encoderSpeedL + encoderSpeedR) / 2)), motorLowBackward, motorHighBackward);

    int magL, magR;
    if (eL > eR)
    {
      magL = mag - 6;
      magR = mag + 2;
    }
    else
    {
      magL = mag + 2;
      magR = mag - 6;
    }

    if (speedRun > 0)
      sendMotorCommand(magL, magR);
    else
      sendMotorCommand(-magL, -magR);



  }
  else
  {
    motorOutput.updateTarget(abs(speedRun));
    int mag;
    if (speedRun > 0)
      mag = constrain(abs(motorOutput.updateOutput((encoderSpeedL + encoderSpeedR) / 2)), motorLowForward, motorHighForward);
    else
      mag = constrain(abs(motorOutput.updateOutput((encoderSpeedL + encoderSpeedR) / 2)), motorLowBackward, motorHighBackward);

    int magL = mag, magR = mag;
    if (speedRun > 0)
    {
      if ((eL > eR) && (macroAngle < 0))
      {
        magL = mag - 6;
        magR = mag + 2;
      }
      else if ((eL < eR) && (macroAngle > 0))
      {
        magL = mag + 2;
        magR = mag - 6;
      }
    }
    else
    {
      if ((eL > eR) && (macroAngle > 0))
      {
        magL = mag - 6;
        magR = mag + 2;
      }
      else if ((eL < eR) && (macroAngle < 0))
      {
        magL = mag + 2;
        magR = mag - 6;
      }
    }


    if (speedRun > 0)
      sendMotorCommand(magL, magR);
    else
      sendMotorCommand(-magL, -magR);
//    Serial.print(lM);
//    Serial.print(",");
//    Serial.print(rM);
//    Serial.print(",");
//    Serial.print(speedRun);
//    Serial.print(",");
//    Serial.print(encoderSpeedL);
//    Serial.print(",");
//    Serial.print(encoderSpeedR);
//    Serial.print(",");
//    motorOutput.verboseCalc();
  }
}








//Encoder feedback to control speed
//speed is a positive or negative number representing a control speed
void motorOutputControlDig(int speedRun)
{
  motorOutput.updateTarget(abs(speedRun));
  int mag;
  if (speedRun > 0)
    mag = constrain(abs(motorOutput.updateOutput((encoderSpeedL + encoderSpeedR) / 2)), motorLowDig, motorHighDig);
  else
    mag = constrain(abs(motorOutput.updateOutput((encoderSpeedL + encoderSpeedR) / 2)), motorLowDig, motorHighDig);
  if (speedRun > 0)
    sendMotorCommand(mag, mag);
  else
    sendMotorCommand(-mag, -mag);

}

void motorOutputControlCorrectDig(int speedRun, int eL, int eR, bool useGyro)
{
  if (!useGyro)
  {
    motorOutput.updateTarget(abs(speedRun));
    int mag;
    if (speedRun > 0)
      mag = constrain(abs(motorOutput.updateOutput((encoderSpeedL + encoderSpeedR) / 2)), motorLowDig, motorHighDig);
    else
      mag = constrain(abs(motorOutput.updateOutput((encoderSpeedL + encoderSpeedR) / 2)), motorLowDig, motorHighDig);

    int magL, magR;
    if (eL > eR)
    {
      magL = mag - 6;
      magR = mag + 2;
    }
    else
    {
      magL = mag + 2;
      magR = mag - 6;
    }

    if (speedRun > 0)
      sendMotorCommand(magL, magR);
    else
      sendMotorCommand(-magL, -magR);


  }
  else
  {
    motorOutput.updateTarget(abs(speedRun));
    int mag;
    if (speedRun > 0)
      mag = constrain(abs(motorOutput.updateOutput((encoderSpeedL + encoderSpeedR) / 2)), motorLowDig, motorHighDig);
    else
      mag = constrain(abs(motorOutput.updateOutput((encoderSpeedL + encoderSpeedR) / 2)), motorLowDig, motorHighDig);

    int magL = mag, magR = mag;
    if (speedRun > 0)
    {
      if ((eL > eR) && (macroAngle < 0))
      {
        magL = mag - 6;
        magR = mag + 2;
      }
      else if ((eL < eR) && (macroAngle > 0))
      {
        magL = mag + 2;
        magR = mag - 6;
      }
    }
    else
    {
      if ((eL > eR) && (macroAngle > 0))
      {
        magL = mag - 6;
        magR = mag + 2;
      }
      else if ((eL < eR) && (macroAngle < 0))
      {
        magL = mag + 2;
        magR = mag - 6;
      }
    }


    if (speedRun > 0)
      sendMotorCommand(magL, magR);
    else
      sendMotorCommand(-magL, -magR);

  }
}

