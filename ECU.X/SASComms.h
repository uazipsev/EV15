/* 
 * File:   SASComms.h
 * Author: User
 *
 * Created on June 7, 2015, 7:35 PM
 */

#ifndef SASCOMMS_H
#define	SASCOMMS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "ADDRESSING.h"
#include <stdbool.h>

#define TRIP_THROTTLE 10
#define TRIP_BRAKE    10

#define CLOSE_COMM_TIME    4
#define BOARD_TIMEOUT     45
#define BOARD_RESEND_MIN  15
    //SAS
    extern volatile unsigned int SASTimer;
    extern unsigned int throttle1, throttle2, brake;

    extern void sendData1(unsigned char whereToSend);
    extern bool receiveData1();
    extern void ToSend1(const unsigned char where, const unsigned int what);
    extern volatile int receiveArray1[20];

    extern void sendData2(unsigned char whereToSend);
    extern void ToSend2(const unsigned char where, const unsigned int what);


    extern void RS485_Direction1(int T_L);
    bool checkSASInputs(unsigned int t1, unsigned int t2, unsigned int b);
    void debugSAS();

#ifdef	__cplusplus
}
#endif

#endif	/* SASCOMMS_H */

