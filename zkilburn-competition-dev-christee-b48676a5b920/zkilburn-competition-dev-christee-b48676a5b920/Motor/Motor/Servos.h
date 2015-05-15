//servos.h
#define UP 254
#define DOWN 253
#define STOP 255
#define UPOVERRIDE 252
#define DOWNOVERRIDE 251
#define lowerLIMIT 6
#define upperLIMIT 93

//// attage names to servos
static Servo leftMotor;
static Servo rightMotor;
static Servo actuator;

static int currentLeftMotorSpeed = 0;
static int currentRightMotorSpeed = 0;
static int currentActuatorSpeed = 0;

// atteches pins to the servo commands
void initializeServos()
{
  leftMotor.attach(5);
  rightMotor.attach(6);
  actuator.attach(3);
}

inline static void updateRamp()
{
  static unsigned long currentMotorLeft = 0;
  static unsigned long previousMotorLeft = 0;
  static unsigned long currentMotorRight = 0;
  static unsigned long previousMotorRight = 0;
  static unsigned long currentActuator = 0;
  static unsigned long previousActuator = 0;


  unsigned long curTime = millis();
  currentMotorLeft = curTime;
  currentMotorRight = curTime;
  currentActuator = curTime;



  if((currentMotorLeft - previousMotorLeft) > time[(currentLeftMotorSpeed + 90)])
  {
    previousMotorLeft = currentMotorLeft;
    if(currentLeftMotorSpeed < leftMotorSpeed)
    {
      currentLeftMotorSpeed += 1;
    }
    else if(currentLeftMotorSpeed > leftMotorSpeed)
    {
      currentLeftMotorSpeed -= 1;
    }
    else
    {
      currentLeftMotorSpeed = leftMotorSpeed;
    }

  }

  if((currentMotorRight - previousMotorRight) > time[(currentRightMotorSpeed + 90)])
  {
    previousMotorRight = currentMotorRight;

    if(currentRightMotorSpeed < rightMotorSpeed)
    {
      currentRightMotorSpeed += 1;
    }
    else if(currentRightMotorSpeed > rightMotorSpeed)
    {
      currentRightMotorSpeed -= 1;
    }
    else
    {
      currentRightMotorSpeed = rightMotorSpeed;
    }
  }

  if(currentActuator - previousActuator > 5)
  {
    previousActuator = currentActuator;

    if(currentActuatorSpeed < actuatorSpeed)
    {
      currentActuatorSpeed += 1;
    }
    else if(currentActuatorSpeed > actuatorSpeed)
    {
      currentActuatorSpeed -= 1;
    }
    else
    {
      currentActuatorSpeed = actuatorSpeed;
    }
  }

  if(actuatorSpeed == 255 || leftMotorSpeed == 255 || rightMotorSpeed == 255)
  {
    currentLeftMotorSpeed = 0;
    currentRightMotorSpeed = 0;
    currentActuatorSpeed = 0;
  }
}


inline static void updateSpeeds()
{
  leftMotor.write((currentLeftMotorSpeed + 90));
  rightMotor.write((currentRightMotorSpeed + 90));
  actuator.write((currentActuatorSpeed + 90));
}

inline void updateServos()
{
  updateRamp();
  updateSpeeds();
  setAct(actuatorValue);
}



inline int setAct(int act){
  static int value; 
  value = updateAngle();
  switch(act)
  {
    case UP:
      if (value<upperLIMIT){
        actuatorSpeed= constrain(upperLIMIT-value,40,90);  
      }
      else
        actuatorSpeed=0;
      break;
    case DOWN:
      if (value>lowerLIMIT){
        actuatorSpeed= constrain(-(value-lowerLIMIT),-90,-40);  
      }
      else
       actuatorSpeed=0;
      break;
    case STOP:
      actuatorSpeed=0;
      break;
    case UPOVERRIDE:      
      actuatorSpeed= 90;  
      break;
    case DOWNOVERRIDE:      
      actuatorSpeed= -90;  
      break;
    default:
      if((act<=90)&&(act>=0)){
        if(!((value>(act-5))  &&   (value< (act+5)))){
          if (value>act){
            actuatorSpeed= constrain(-(act-value),-90,-40);
          }
          else if(value<act){
            actuatorSpeed= constrain((act-value),40,90);        
          }
         
        }
        else {
          actuatorValue=255;
          actuatorSpeed=0;
        }
      }
      break;
  }
}


//
////actuator help method  -- send a speed of adjustment
//inline void actuatorAdjust(int mag) {
//  //limit commanded speed to range -90->90
//  if (abs(mag) > 90)  {
//    if (mag < 0)   mag = -90;
//    if (mag > 0)   mag =  90;
//  }
//  //make sure the movement isnt too slow
//  if (abs(mag) < 50)  {
//    if (mag < 0)   mag = -50;
//    if (mag > 0)   mag =  50;
//  }
//  outMotor.actuator = mag;
//}
//
////-----------------------------------------------------------------------------------
////set the actuator to the angle specified
//inline bool actuator(int target)
//{
//  continueMacro = 0;
//  int magnitude;
//  //while the actuator is not at the target(within 1)
//  while (!(actuatorAngle >= target - 1 && actuatorAngle <= target + 1) && continueMacro == 0)
//  {
//    //update the value of the actuator
//    actuatorUpdate();
//    //choose how fast to command
//    magnitude = (target - actuatorAngle) * 5;
//    //set actuator movement to that speed(signed direction)
//    actuatorAdjust(magnitude);
//    //send motor data
//    to_motor.sendData();
//
//
//    //check for command halt
//    if (from_control.receiveData())
//    {
//      //report to the screen
//      updateScreen();
//      continueMacro = fromControl.macro_stop;
//    }
//  }
//  //end command
//  allStop();
//  motor_unStick();
//
//  //return if halt
//  return (continueMacro == 0);
//}
//
//




