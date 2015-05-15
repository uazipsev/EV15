//macros_actuator.h

int angleSetIn;
inline bool sendActuatorPosition(int angle)
{  
  int count=0;
  while((macro_stop!=1)&&(count<85))
  {
    sendActuatorCommand(angle);
    macroCommunicationsUpdate();
    count++;
    delay(50); 
  }
  sendActuatorCommand(255);

  return (macro_stop == 0);
}
inline bool sendActuatorPositionFeedback(int angle)
{  
  
  while((macro_stop!=1)&&(!isAbout(motor_bucket_angle,angle,2)))
  {
    sendActuatorCommand(angle);
    macroCommunicationsUpdate();
    delay(50); 
  }
  sendActuatorCommand(255);

  return (macro_stop == 0);
}
inline bool sendActuatorPositionDig(int angle)
{  
  int count=0;
  while((macro_stop!=1)&&(!isAbout(motor_bucket_angle,angle,2)))
  {
    if(angle<BUCKET_DIG_DRIVE_BEGIN_ANGLE)
    {
    sendMotorCommand(15,15,angle);
    }
    else sendActuatorCommand(angle);
    macroCommunicationsUpdate();
    count++;
    delay(50); 
  }
  sendMotorCommand(0,0,255);

  return (macro_stop == 0);
}
void fullDigRoutine()
{
  sendActuatorPosition(BUCKET_DRIVE_ANGLE_SET);
  sendActuatorPositionDig(BUCKET_DIG_ANGLE_SET);
  runEncoderDistanceEvenly(DIG_DRIVE_DISTANCE);
  sendActuatorPosition(BUCKET_DRIVE_ANGLE_SET + 25);
  sendActuatorPosition(BUCKET_DRIVE_ANGLE_SET);
  runEncoderDistanceEvenly(-25);
  sendActuatorPosition(BUCKET_DUMP_ANGLE_SET);
  delay(DELAY_BUCKET_EMPTY);
  sendActuatorPosition(BUCKET_DRIVE_ANGLE_SET);
}
void bucketMovementDig()
{
  sendActuatorPosition(BUCKET_DRIVE_ANGLE_SET);
  delay(750);
  sendActuatorPosition(BUCKET_DIG_ANGLE_SET);
  delay(750);
  sendActuatorPosition(BUCKET_DRIVE_ANGLE_SET);
}

void bucketMovementDump()
{
  sendActuatorPosition(BUCKET_DRIVE_ANGLE_SET);
  delay(750);
  sendActuatorPosition(BUCKET_DUMP_ANGLE_SET);
  delay(DELAY_BUCKET_EMPTY);
  sendActuatorPosition(BUCKET_DRIVE_ANGLE_SET);
}

