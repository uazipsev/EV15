
int navMacro = 0;
bool macro_active = false;
bool macro_complete;
bool macro_in_progress = false;
//gyroscope tracking for calibrations
int numberRuns = 0;
bool firstShot = true;
//bool readyToSend = false, readyToSend2 = false;
//-----------------------Library based Timers-------------------------
Timers LEDtimer(250);
Timers sensorTimer(4);
Timers commTimer(1000);
Timers screenTimer(24);
//PID systems timer
Timers PIDTimer(25);
//Communications adjustment
//Timers latency(8);//8
//Timers latency2(50);
Timers sendTime(500);
//arduino helper sensorBaord update rate
Timers checkPacket(5);

int macro_command;
int macro_sub_command;



//Error State
int debug;
int errorState = 0;

  int controlStop=0;

//------------------------EasyTransfer vars---------------------------
//EasyTransferCRC from_control;
//EasyTransferCRC to_control;
EasyTransferCRC sensorBoard;
//EasyTransferCRC to_Nav;
//EasyTransferCRC from_Nav;
EasyTransferCRC to_LED;
//----------------------FastTransfer Vars---------------------------
//ADDRESSING FOR ROBOT
#define COMMUNICATIONS_ADDRESS     1
#define CONTROL_ADDRESS            2
#define NAVIGATION_ADDRESS         3
#define PIC_ADDRESS                4
#define MOTOR_ADDRESS              5
#define LED_ADDRESS                6
#define POWER_ADDRESS	           7

FastTransfer NavigationBoard;
int navigationReceive[15];

//COMMUNICATIONS SEND = Navigation
#define MACRO_COMMAND_NAV_SEND                   1
#define MACRO_SUB_COMMAND_NAV_SEND               2
#define MACRO_STOP_NAV_SEND                      3
#define LEFTMOTORSPEED_NAV_SEND                  4
#define RIGHTMOTORSPEED_NAV_SEND                 5
#define ACTUATOR_NAV_SEND                        6

//Communications RECEIVE - Navigation
#define MACRO_COMMAND_NAV_RECEIVE                   1
#define MACRO_SUB_COMMAND_NAV_RECEIVE               2
#define MACRO_COMPLETE_NAV_RECEIVE                  3
#define LEFT_MOTOR_NAV_RECEIVE                      4
#define RIGHT_MOTOR_NAV_RECEIVE                     5
#define VOLTS_NAV_RECEIVE                           6
#define AMPS_NAV_RECEIVE                            7
#define AMPHOUR_NAV_RECEIVE                         8
#define ENCODERRIGHT_NAV_RECEIVE                    9
#define ENCODERLEFT_NAV_RECEIVE                     10
#define ENCODERSPEEDR_NAV_RECEIVE                   11
#define ENCODERSPEEDL_NAV_RECEIVE                   12
#define GYRO_NAV_RECEIVE                            13


FastTransfer ControlBoard;
int controlReceive[15];

//COMMUNICATIONS RECEIVE - CONTROL
#define LEFTMOTORSPEED_CONTROL_RECEIVE         1
#define RIGHTMOTORSPEED_CONTROL_RECEIVE        2
#define ACTUATOR_CONTROL_RECEIVE               3
#define MACRO_COMMAND_CONTROL_RECEIVE          4
#define MACRO_SUB_COMMAND_CONTROL_RECEIVE      5
#define MACRO_STOP_CONTROL_RECEIVE             6
#define COLOR_PICKER_CONTROL_RECEIVE           7
#define LED_UPDATE_INDICATOR_CONTROL_RECEIVE   8
#define LED_STATE_OVERRIDE_CONTROL_RECEIVE     9

//COMMUNICATIONS SENDING
#define MACRO_COMMAND_CONTROL_SEND             1
#define GYRO_CONTROL_SEND                      2
#define LEFT_MOTOR_CONTROL_SEND                3  
#define RIGHT_MOTOR_CONTROL_SEND               4
#define VOLTS_CONTROL_SEND                     5
#define AMPS_CONTROL_SEND                      6
#define AMPHOUR_CONTROL_SEND                   7
#define ENCODERSPEEDL_CONTROL_SEND             8
#define ENCODERSPEEDR_CONTROL_SEND             9
#define ENCODERRIGHT_CONTROL_SEND              10
#define ENCODERLEFT_CONTROL_SEND               11
#define MACRO_COMPLETE_CONTROL_SEND            12
//------------------------Autonomous vars---------------------------
int autoSet = 0;
int autoState = 0;

//------------------------Sensors vars---------------------------
#define SIZE 20
//array for data storage
int d0[SIZE];
int d1[SIZE];
int d2[SIZE];
int d3[SIZE];
int d4[SIZE];
int d5[SIZE];
//calculation variables
int stddev0, avg0;
int stddev1, avg1;
int stddev2, avg2;
int stddev3, avg3;
int stddev4, avg4;
int stddev5, avg5;
//data array pointer
int index = 0;
//Data points from sensor board
float D0, D1, D2, D3, D4, D5;

//------------------------Gyroscope  vars---------------------------
int8_t swap;
int macroAngle;
static float zFilt;
static int16_t offset, high, low, z_dead_g;
static float zRaw, zDeg, zRot;
static float dt;
static float compare;
static int16_t samples[500];
static float lastTime;
static float now;
static int error;
float persistentAngle;
int latestFilteredSample = 0;

//------------------------LED  vars---------------------------
int prevColor = 0;
//static Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//------------------------STATE  vars---------------------------
//this is the state stacee is in
// 0 = no comms
// 1 = manual drive
// 2 = autonomous
// the inicial state assumes no comms
int currentState = 0;

//------------------------Screen Data vars---------------------------
//Actuator storage
int actuatorAngle = 0;
//output for heading
int robotHeading = 0;
//------------------------COMM vars---------------------------
int sender = 0;
//---------------------------Power Vars----------------------
int volts, amps, watts;
