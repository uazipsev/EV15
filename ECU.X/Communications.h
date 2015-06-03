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

enum bus1CommState{SAS_UPDATE=0, DDS_UPDATE=1, PDU_UPDATE=2, CHECK_STATE1=3, ERROR_STATE1=4, NUM_STATES1=5};
enum bus1CommState commsBus1State=SAS_UPDATE;

enum bus2CommState{MCS_UPDATE=0,CHECK_STATE2=1,ERROR_STATE2=2,NUM_STATES2=3};
enum bus2CommState commsBus2State=MCS_UPDATE;

bool readyToSendSAS = true;
bool readyToSendDDS = true;
bool readyToSendPDU = true;
bool readyToSendMCS = true;

bool SAS_COMMS_ERROR = false;
bool DDS_COMMS_ERROR = false;
bool MCS_COMMS_ERROR = false;
bool PDU_COMMS_ERROR = false;

void updateComms();
void sendErrorCode();
void sendErrorCode2();
void RS485_Direction1(int T_L);
void RS485_Direction2(int T_L);

void checkCommDirection();
void checkCommDirection1();
void bus1Update();
void bus2Update();


bool receiveCommSAS();
bool receiveCommDDS();
bool receiveCommMCS();
bool receiveCommPDU();


bool requestSASData();
bool requestDDSData();
bool requestMCSData();
bool requestPDUData();

void resetCommTimers();
void resetCommTimers2();


extern unsigned int indicators;
extern unsigned int buttons;

#ifdef	__cplusplus
}
#endif

#endif	/* COMMUNICATIONS_H */
