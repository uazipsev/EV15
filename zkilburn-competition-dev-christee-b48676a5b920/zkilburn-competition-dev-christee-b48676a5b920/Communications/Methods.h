

/******************************************************************************/
/*                           Method Declarations                              */
/******************************************************************************/
void selectCommLines(int comm);

void packetWait();
/*********************************************************/
/*             Sensors.h Method Declarations             */
/*********************************************************/
//Helper methods
int validRead(int signal,  int average);            //only believe and store a %value of sensor change
bool varIsAbout(int var, int val, int plusMinus);   //compare a variable to a value and check if its within rangel

//given a raw sensor value do a calculation to determine distance in cm
float calcLongIR(float rawValue, int sensor);
float calcMidIR(float rawValue);
float calcFrontStereo(float rawValue, int sensor);
float calcBackStereo(float rawValue);

//Given all of the sensor inputs per side, select which value is valid and use it as side reading
int selectFront(int LongF, int midL, int midR, int prev);
int selectSide(int LongS, int midS, int prev);
int selectBack(int LongB, int midB, int shortL, int shortR, int prev);

bool midFCheck(int MF);   //check 20-150
bool longCheck(int L);    //check 75-550
bool midCheck(int M);     //check 10-80
bool shortCheck(int S);   //check 2-30

int avgF(int L, int M1, int M2);        //Average the front values to aquire an initial value
int avgB(int L, int M, int S1, int S2); //Average the back values to aquire an initial value
int avgS(int L, int M);                 //Average the side values to aquire an initial value
inline void initIR();
void IRinputInit();
void IRoutputPowerInit();

static inline void actuatorUpdate();
void updateIRSensors();

inline void commSafety();


/*********************************************************/
/*              Gyro Method Declarations               */
/*********************************************************/

inline int sampleGyroZ();
int MPU6050_read(int starts, uint8_t *buffer, int sized);

