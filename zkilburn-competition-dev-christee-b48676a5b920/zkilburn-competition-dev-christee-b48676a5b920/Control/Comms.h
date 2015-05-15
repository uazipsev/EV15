//comms.h
FastTransfer robot;
int roboMessage[50];

FastTransfer Bluetooth;
int receiveArray[4];

//COMM ADDRESSES
#define CONTROL_ADDRESS            5
#define NAVIGATION_ADDRESS         4
#define PIC_ADDRESS                1
#define MOTOR_ADDRESS              6
#define LED_ADDRESS                2
#define POWER_ADDRESS	           3


//CONTROL RECEIVE STUFF
#define MACRO_COMMAND_RECEIVE        1
#define MACRO_SUB_COMMAND_RECEIVE    2
#define MACRO_COMPLETE               3
#define GYRO_ANGLE                   4
#define MOTORL                       5
#define MOTORR                       6
//POWER
#define VOLTS                        7
#define MILLIAMPS                    8
#define MILLIAMPHOUR                 9
#define WATTHOURS_POWER_RECEIVE      10
//PIC (MAYBE NAV)
#define ENCODERSPEEDL                11
#define ENCODERSPEEDR                12
#define ENCODERRIGHT                 13
#define ENCODERLEFT                  14
//MOTOR
#define BUCKET_ANGLE                 15
//Wii Camera Stuff
#define WII_CAMERA_LEFT_ANGLE        16
#define WII_CAMERA_RIGHT_ANGLE       17
#define WII_CAMERA_LEFT_LOCKED       18
#define WII_CAMERA_RIGHT_LOCKED      19


//CONTROL SEND - ROBOT
//MOTOR
#define LEFTMOTORSPEED              1
#define RIGHTMOTORSPEED             2
#define ACTUATORSPEED               3
//NAVIGATION
#define MACRO_COMMAND_SEND          1
#define MACRO_SUB_COMMAND           2
#define MACRO_STOP                  3
//LED

#define LED_STATE_OVERRIDE          1
#define COLOR_PICKER                2
#define LED_UPDATE_FLAG             3

//PIC
#define ROBOT_MOVING                 1
#define WII_SUBSYSTEM_MODE           2    //MODES INCLUDE: TRIG=0, LEFT_BEACON_ANGLES=1, RIGHT_BEACON_ANGLES=2, CAMERA_OVERRIDE_BEACON_ANGLES=3, CONTINUOUS_AQUISITION=4
#define WII_LEFT_CAMERA_MODE         3    //MODES 3 and 4 only used for WII_SUBSYSTEM_MODE 3   
#define WII_RIGHT_CAMERA_MODE        4            //0=LEFT_BEACON 1=RIGHT_BEACON

void initializeCommunicaton()
{
  //screen init
  Serial3.begin(256000);
  //robot init
  Serial1.begin(115200);
  //bluetooth
  // Serial2.begin(115200);
  //Debug
  Serial.begin(9600);

  robot.begin(Details(roboMessage), CONTROL_ADDRESS, false, &Serial1);
  //Bluetooth.begin(Details(receiveArray), CONTROL_ADDRESS, false, &Serial2);
}

inline void updateCommunication()
{
  static Timers minimumResponseTimer(20);
  //So if you have heard from the comm after sending -or- if the resend timer timed out and you havent already sent before a safety timeout condition
  if ((heardBack && minimumResponseTimer.timerDone()) || (resendTimer.timerDone() && notSent))
  {
    sendDataNavigation(internalMacroKeeper);
    delay(10);
    sendDataMotor(leftMotorSpeed, rightMotorSpeed, actuatorSpeed);
    if (internalMacroKeeper == 0)      ;
    //make a mental note that we have sent
    if (heardBack)  heardBack = false;
    else if (notSent) notSent = false;
  }
  //control box is always listening to the robot
  //in order to keep track of macro's and keep
  //screen up to date.
  if (robot.receiveData())
  {
    //if good checksum, store data locally.
    commMacro             = roboMessage[MACRO_COMMAND_RECEIVE];
    //Gyro Angle
    gyroAngle             = roboMessage[GYRO_ANGLE];
    //Robot Motor States
    motorL                = roboMessage[MOTORL];
    motorR                = roboMessage[MOTORR];
    //Power systems
    volts                 = roboMessage[VOLTS];
    milliamps             = roboMessage[MILLIAMPS];
    milliamphours         = roboMessage[MILLIAMPHOUR];
    bucketAngle           = roboMessage[BUCKET_ANGLE];
    //Encoder Details
    if (roboMessage[ENCODERSPEEDL] != 0)
      encoderSpeedL    = ((encoderSpeedL * 15) + roboMessage[ENCODERSPEEDL]) / 16;
    else
      encoderSpeedL = 0;
    if (roboMessage[ENCODERSPEEDR] != 0)
      encoderSpeedR    = ((encoderSpeedR * 15) + roboMessage[ENCODERSPEEDR]) / 16;
    else
      encoderSpeedR = 0;
    encoderR         = roboMessage[ENCODERRIGHT];
    encoderL         = roboMessage[ENCODERLEFT];
    leftAngle        = roboMessage[WII_CAMERA_LEFT_ANGLE];
    rightAngle       = roboMessage[WII_CAMERA_RIGHT_ANGLE];
    leftLocked       = roboMessage[WII_CAMERA_LEFT_LOCKED];
    rightLocked      = roboMessage[WII_CAMERA_RIGHT_LOCKED];
    //only store the value of the complete macro
    //if we are looking for it
    if (internalMacroKeeper != 0) macro_complete = roboMessage[MACRO_COMPLETE];
    else                          macro_complete = 0;

    //Communications Reset Timers
    heardBack = true;
    notSent = true;
    resendTimer.resetTimer();
    minimumResponseTimer.resetTimer();
    commTimer.resetTimer();
  }

  //  if (Bluetooth.receiveData())
  //  {
  //    static int leftMotorBT, rightMotorBT;
  //    leftMotorBT = receiveArray[0];
  //    rightMotorBT = receiveArray[1];
  //    if ((leftMotorSpeed == 0) && (rightMotorSpeed == 0))
  //    {
  //      robot.ToSend(LEFTMOTORSPEED, leftMotorBT);
  //      robot.ToSend(RIGHTMOTORSPEED, rightMotorBT);
  //    }
  //  }
  
  if (internalMacroKeeper == 0)
  {
    commSafety();
  }
}



inline void commSafety()
{
  commTimer.updateTimer();
  if (commTimer.timerDone())
  {
    packetWait();
    //Safety Timer Reset
    commTimer.resetTimer();
    //Must have heard back because we got out of safety
    heardBack = true;
    //Definitely havent sent a timeout resend
    notSent = true;
    //Reset timer to avoid the accidental send
    resendTimer.resetTimer();
  }
}

inline void killMacro()
{
  sendDataNavigation(0, 0, 1);
  internalMacroKeeper = 0;
  internalSubKeeper = 0;
  ensureReceived(Ending);
  commTimer.resetTimer();
}

inline void packetWait()
{
  leftMotorSpeed = 0;
  rightMotorSpeed = 0;
  actuatorSpeed = 255;
  float time = millis();
  float lastTime = time;
  pageKeeper = activePage;  //record which page is active (to return to after macro)
  CTS = true;
  //writeObject(FORMMESSAGE, CommError, 1);    //change the page to the active macro page
  sendTimer.resetTimer();
  totalTime = 0;
  while (!robot.receiveData())
  {
    uptime = 0;
    updateScreen();
    time = millis();
    if ((abs(time - lastTime)) > 1000) {
      totalTime++;
      lastTime = time;
    }
    sendTimer.updateTimer();
    if (sendTimer.timerDone())
    {
      sendDataNavigation(internalMacroKeeper);
      delay(10);
      sendDataMotor(0, 0, 255);
    }
    if (digitalReadFast(MACRO_BUTTON) == HIGH)
    {
      killMacro();
    }
    delay(100);
    CTS = true;
    //writeObject(LEDDIGITS, 1, totalTime);
  }
  sendLEDdata(3, 0);
  delay(10);
  sendDataNavigation(internalMacroKeeper);
  delay(10);
  sendDataMotor(leftMotorSpeed, rightMotorSpeed, actuatorSpeed);
  commTimer.resetTimer();
  CTS = true;
  //writeObject(FORMMESSAGE, pageKeeper, 1);    //change the page
  CTS = true;
  uptime = 0;
}


void sendDataNavigation(int _macro_command, int _macro_sub_command, int _macro_stop)
{
  robot.ToSend(MACRO_SUB_COMMAND, _macro_sub_command);
  robot.ToSend(MACRO_STOP, _macro_stop);
  robot.ToSend(MACRO_COMMAND_SEND, _macro_command);
  robot.sendData(NAVIGATION_ADDRESS);
}

void sendDataNavigation(int _macro_command)
{
  robot.ToSend(MACRO_COMMAND_SEND, _macro_command);
  robot.sendData(NAVIGATION_ADDRESS);
}

void sendDataMotor(int leftMotor, int rightMotor)
{
  robot.ToSend(LEFTMOTORSPEED  , leftMotor);
  robot.ToSend(RIGHTMOTORSPEED , rightMotor);
  robot.sendData(MOTOR_ADDRESS);
}

void sendDataMotor(int leftMotor, int rightMotor, int actuator)
{
  robot.ToSend(LEFTMOTORSPEED  , leftMotor);
  robot.ToSend(RIGHTMOTORSPEED , rightMotor);
  robot.ToSend(ACTUATORSPEED   , actuator);
  robot.sendData(MOTOR_ADDRESS);
}

void sendDataMotor(int actuator)
{
  robot.ToSend(ACTUATORSPEED   , actuator);
  robot.sendData(MOTOR_ADDRESS);
}

void sendLEDdata(int stateOverride, int colorPicker)
{
  robot.ToSend(LED_STATE_OVERRIDE, stateOverride);
  robot.ToSend(COLOR_PICKER, colorPicker);
  robot.ToSend(LED_UPDATE_FLAG, 1);
  robot.sendData(LED_ADDRESS);
}









