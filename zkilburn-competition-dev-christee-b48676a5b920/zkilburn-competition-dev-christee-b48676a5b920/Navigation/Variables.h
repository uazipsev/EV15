
/*********************TUNING VARIABLES DATA*************************/
int slowingDistance = 250;
int actuatorDrivingAngle = 40;
//PID IR FOLLOW
float sideKpL = 1.35, sideKdL = 180000000, sideKiL = 0; // Kp  0.025 40000000 0.06
float sideKpR = 1.35, sideKdR = 180000000,  sideKiR = 0; //0.078


/*********************AUTO SENSOR DATA*************************/
//----------MPU DATA----------------
MPU MPU1(0x68);
MPU MPU2(0x69);
int sampleSet[100];
//GYRO
Filter gyroF1, gyroF2;
int angle1, angle2;
int macroAngle;
//gyroscope set angle (used for turning)
int angleSet;
//Accelerometer
Filter accelF1, accelF2;
int velocity1, velocity2;
float now, last;
int travelD1;
int travelD2;
int totalTravelD;
//ACTUATOR DATA
int actuatorAngle;
//ENCODER DATA
int encoder1, encoder2;
float encoderR=0, encoderL=0;
unsigned int encoderSpeedR=9999, encoderSpeedL=9999;
//Motor DATA 
int lM, rM;
/*********************AUTO CONTROL DATA*************************/
int stored_macro_command;
int macro_sub_command;
int sub_command = 0;
bool macro_stop;
bool continuable;
int continueMacro = 0;

/********************* CONTROL TIMERS *************************/
Timers PIDTimer(5);
Timers PIDTimer2(100);
Timers latency(5);
Timers decisionTimer(50);
Timers linkTimer(50);
Timers safetyTimer(2000);
Timers sendTimer(50);
Timers MPUTimer(20);

/***************Communications variables*******************/
bool readyToSend = false;














