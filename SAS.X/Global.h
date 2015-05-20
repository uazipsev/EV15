/* 
 * File:   Global.h
 * Author: Rick
 *
 * Created on May 17, 2015, 2:39 AM
 */

#ifndef GLOBAL_H
#define	GLOBAL_H

#define UART_BUFFER_SIZE 200

int distanceInches[4];
int pulseCount[5];
extern unsigned int throttle1, throttle2;

extern unsigned int brake1, brake2;

extern bool startHeard,me,stop1,packetReady;
extern unsigned char inputCmd;
extern int counter;
//variable declarations/initialization
extern int ECUbyteNum, ECUpacketSize;
extern int slaveByteNum, slavePacketSize;
char slaveAddr;
extern unsigned char ECUOut[7];
//unsigned char SlaveOut[5];
extern bool slaveSent;
extern float slaveTime, LEDTime;
extern bool responseSent;
extern int i;
extern int heard;
extern int dataIn;
extern bool CRC1;
extern int receiveArray[20];

#endif	/* GLOBAL_H */

