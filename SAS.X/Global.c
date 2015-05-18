#include <stdbool.h>
#include "Global.h"


int distanceInches[4];
int pulseCount[5];
unsigned int throttle1=1, throttle2=2;

unsigned int brake1=3, brake2=4;
int speed1=5, speed2=6, speed3=7,speed4=8;

bool startHeard,me,stop1,  packetReady;
unsigned char inputCmd;
int counter;
bool checkBatteryRequest=false;
int batteryToCheck=0;
int batteryVolts[28];
//variable declarations/initialization
int ECUbyteNum = 99, ECUpacketSize;
int slaveByteNum = 99, slavePacketSize;
char slaveAddr;
unsigned char ECUOut[7];
//unsigned char SlaveOut[5];
bool slaveSent = 1;
float slaveTime = 0, LEDTime = 0;
bool responseSent=1;
int i;
int heard=0;
int dataIn=0;
bool CRC1=0;
int receiveArray[20];

