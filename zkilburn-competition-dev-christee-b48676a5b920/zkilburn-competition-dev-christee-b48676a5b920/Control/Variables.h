
Timers LEDTimer(1000);
Timers Seconds(1000);
Timers sendTimer(100);
Timers screenTimer(25);  //15
Timers commTimer(2000);
Timers latency(50);
Timers resendTimer(50);
bool CTS=true;
bool notSent=true, heardBack=false;
//---------------------- Screen variables ---------------------------
//KEEPER OF WHICH PAGE THE SCREEN IS READING
int activePage = 0;
int pageKeeper = 0;
//Time connected
int uptime = 0;
//Time disconnected
uint16_t totalTime = 0;
//Gyro Variables
int calcHeading = 0;
int angleOffset = 0;
int gyroAngle = 999;
int robotHeading = 0;
int outputHeading = 0;
//Power Variables
float milliamphours;
float volts = 2600;
float milliamps = 200, watts;
//Encoder Variables
float encoderR=9999;
float encoderL=9999;
unsigned int encoderSpeedR=9999, encoderSpeedL=9999;
//Motor Values
int motorL=85;
int motorR=15;
//PID values
int errorMargin = 25;
int derivative=5;
int integral=10;
//-----------for constants send screen-------------------------------
bool variableChosen = false;
bool valueChosen = false;
int variableRequest, valueRequest;
int thousands, hundreds, tens, ones, stored;
int lastWrite = 0;
int largeOnes = 0, largeTens = 0, tenToThe = 0;
bool large = false, storeLarge = false, negative = false;
int valueDispInt, valueDispExp, workingRegDisp;
bool valueDispNeg = false;
//------------------helpful variable---------------------------
int plyable;
int handy = 0;
bool booly = false;
//----------------Tuning Variables--------------------------
int gyroConLow = 15;
int gyroConHigh = 40;
int motorConLow = 8;
int motorConHigh = 18;
//-----------------internalized vars of robot data------------------------
//------------------------------------------------------------------------
int bucketAngle = 999;
//Generic Debug Variables
int debug1;
int debug2;
int debug3;
int debug4;

//ACTUATOR DATA UPDATES
int actuatorData = 30;
//VARIABLE TO CATCH REQUESTS FROM SCREEN
int diff_turn = 0;       //L/R DIFF
int driveDistance = 0;   //F/R DIFF
//command angle for gyroscope knob
int angle_command = 0;
//----------------------------------------------------------------------------
//in development profile variable for changing driving functionality
int drivingProfile = 1;
//State Control Variables
int leftMotorSpeed = 0;
int rightMotorSpeed = 0;
int actuatorSpeed = 0;
//comboard macroback
int commMacro = 0;
int macro_complete = 0;
//macro keeper here on control
int internalMacroKeeper=0;
int internalSubKeeper;
//screen macro controls
int macro_command_screen = 0;
int macro_sub_command = 0;
int encoderValue=0;
int setAngle=0;

//WiiVariables
int leftAngle, rightAngle;
bool leftLocked, rightLocked;


//checksum for screen comm
int checksum = 0;
//counter for ensured data packet flow
int sender = 0;
//package for screen comm packet
byte receivedPack[6];


