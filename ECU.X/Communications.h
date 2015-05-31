/* 
 * File:   Communications.h
 * Author: User
 *
 * Created on May 31, 2015, 3:26 PM
 */

#ifndef COMMUNICATIONS_H
#define	COMMUNICATIONS_H

#ifdef	__cplusplus
extern "C" {
#endif


extern void RTD(int lenth);

extern void sendData(unsigned char whereToSend);
extern bool receiveData();
extern void ToSend(const unsigned char where, const unsigned int what);
extern volatile int receiveArray[20];
extern bool Transmit_stall;
extern volatile unsigned int talkTime;

extern void sendData1(unsigned char whereToSend);
extern bool receiveData1();
extern void ToSend1(const unsigned char where, const unsigned int what);
extern volatile int receiveArray1[20];
extern bool Transmit_stall1;
extern volatile unsigned int talkTime1;

extern void sendData2(unsigned char whereToSend);
extern bool receiveData2();
extern void ToSend2(const unsigned char where, const unsigned int what);
extern volatile int receiveArray2[20];
extern bool Transmit_stall2;
extern volatile unsigned int talkTime2;

extern void sendData3(unsigned char whereToSend);
extern bool receiveData3();
extern void ToSend3(const unsigned char where, const unsigned int what);
extern volatile int receiveArray3[20];
extern bool Transmit_stall3;
extern volatile unsigned int talkTime3;

extern volatile unsigned int SASTimer, DDSTimer, MCSTimer, PDUTimer,BootTimer;

enum commState{SAS_UPDATE=0, DDS_UPDATE=1, CHECK_STATE=2, ERROR_STATE=4, NUM_STATES=5};

enum commState commsState=SAS_UPDATE;

bool readyToSendSAS = true;
bool readyToSendDDS = true;

bool SAS_COMMS_ERROR = false;
bool DDS_COMMS_ERROR = false;
bool MCS_COMMS_ERROR = false;

void updateComms();
void sendErrorCode();
void RS485_Direction1(int T_L);
void RS485_Direction2(int T_L);

void checkCommDirection();
void checkCommDirection1();
void receiveComm();
void receiveComm1();

bool receiveCommSAS();
bool receiveCommDDS();
bool requestSASData();
bool requestDDSData();
void requestMCSData();
void requestPDUData();


#ifdef	__cplusplus
}
#endif

#endif	/* COMMUNICATIONS_H */

