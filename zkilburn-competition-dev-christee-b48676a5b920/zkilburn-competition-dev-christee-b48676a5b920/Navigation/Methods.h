//Methods.h





/*********************************************************/
/*        Communications Method Declarations             */
/*********************************************************/
void pullDataFromPacket();
void updateFromControlBoard();
void updateMotorCommunications();
void updatePICCommunications();
inline void initializeCommunications();
inline void updateComms();
inline void commSafety();
inline void packetWait();
inline void USBdebug();


/*********************************************************/
/*             Autonomous Method Declarations             */
/*********************************************************/
//Autonomous features methods
void updateAutonomous();
inline bool straightShot(bool continuable);
bool fixPositionX(int currentX, int targetX, int direction);
bool fixPositionY(int currentY, int targetY, int direction);
bool makeHeading(int globalAngle);
bool followMap(int location, int direction);
void encoderRun1();
void encoderRun2();
void encoderRun3();
void wipeEncoders();
void runEncoderDistance(int cm);
void runEncoderDistanceEvenly(float cm);
bool wiiCameraLocalize(int targetBeacon, int targetCenter, int cameraNumber);
inline bool orientWithWii();
inline bool straightPathMineDump();
inline void terminateMacroSystem();
void sendActuatorCommand(int actuator);
void sendMotorCommand(int leftMotor, int rightMotor, int actuator);
void sendMotorCommand(int leftMotor, int rightMotor);
/*********************************************************/
/*               Macro Method Declarations               */
/*********************************************************/
//Macro System Features Methodsinline 
void macroCommunicationsUpdate();
inline driveData formatDifferentialDrive(int mag, int offset);
inline bool doTurn(int setAngle);
inline bool sendActuatorPosition(int angle);
inline bool waitForActuator(int delayTime);
inline void initMacroSystem();
inline void finishMacro();
inline void betweenMacro();
inline void allStop();
inline void motor_unStick();
inline bool turn(int setAngle);
inline void updateScreen();
void fullRoutine();
void fullDigRoutine();
void driveDigDistance();
void bucketMovementDig();
void bucketMovementDump();
void fiftyForwardFiftyBackward();
void squareRoutine();

/*********************************************************/
/*              Gyro Method Declarations               */
/*********************************************************/


void updateMPU();
void initMPUFilters();

bool isAbout(int var, int val, int plusMinus) {
  return ((var < val + plusMinus) && (var > val - plusMinus));
}

/*********************************************************/
/*              Motor Method Declarations               */
/*********************************************************/
void motorOutputControlCorrectDig(int speedRun, int eL, int eR, bool useGyro);
void motorOutputControlDig(int speedRun);
void motorOutputControlCorrect(int speedRun, int eL, int eR);
void motorOutputControlCorrect(int speedRun, int eL, int eR, bool useGyro);
void motorOutputControl(int speedRun);
void motorOutputControlRight(int speedRun);
void motorOutputControlLeft(int speedRun);
