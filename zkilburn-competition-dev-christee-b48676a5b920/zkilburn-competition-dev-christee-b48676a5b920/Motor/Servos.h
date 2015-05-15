//servos.h
#define UP 254
#define DOWN 253
#define STOP 255
#define UPOVERRIDE 252
#define DOWNOVERRIDE 251
#define lowerLIMIT 6
#define upperLIMIT 90
#define ACTUATOR_DEADBAND 3
#define ACTUATOR_SPEED_LOWER_LIMIT 55
#define ACTUATOR_SPEED_UPPER_LIMIT 90

#define VIBRATING_MOTOR_ON_HIGH 80
#define VIBRATING_MOTOR_ON_LOW 10
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
  bucketAngle = updateAngle();
  switch(act)
  {
    case UP:
      if (bucketAngle<upperLIMIT){
        actuatorSpeed= constrain(upperLIMIT-bucketAngle,ACTUATOR_SPEED_LOWER_LIMIT,ACTUATOR_SPEED_UPPER_LIMIT);  
      }
      else
        actuatorSpeed=0;
      break;
    case DOWN:
      if (bucketAngle>lowerLIMIT){
        actuatorSpeed= constrain(-(bucketAngle-lowerLIMIT),-ACTUATOR_SPEED_UPPER_LIMIT,-ACTUATOR_SPEED_LOWER_LIMIT);  
      }
      else
       actuatorSpeed=0;
      break;
    case STOP:
      actuatorSpeed=0;
      break;
    case UPOVERRIDE:      
      actuatorSpeed= ACTUATOR_SPEED_UPPER_LIMIT;  
      break;
    case DOWNOVERRIDE:      
      actuatorSpeed= -ACTUATOR_SPEED_UPPER_LIMIT;  
      break;
    default:
      if((act<=93)&&(act>=0)){
        if(!((bucketAngle>(act-ACTUATOR_DEADBAND))  &&   (bucketAngle< (act+ACTUATOR_DEADBAND)))){
          
          if (bucketAngle>act){
            actuatorSpeed= constrain(-(act-bucketAngle),-ACTUATOR_SPEED_UPPER_LIMIT,-ACTUATOR_SPEED_LOWER_LIMIT);
          }
          else if(bucketAngle<act){
            actuatorSpeed= constrain((act-bucketAngle),ACTUATOR_SPEED_LOWER_LIMIT,ACTUATOR_SPEED_UPPER_LIMIT);        
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

