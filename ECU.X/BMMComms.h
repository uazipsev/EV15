/* 
 * File:   BMMComms.h
 * Author: User
 *
 * Created on June 7, 2015, 7:38 PM
 */

#ifndef BMMCOMMS_H
#define	BMMCOMMS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "ADDRESSING.h"
#include <stdbool.h>

#define CLOSE_COMM_TIME    4
#define BOARD_TIMEOUT     45
#define BOARD_RESEND_MIN  15

    extern volatile unsigned int BMMTimer;
    extern void sendData(unsigned char whereToSend);
    extern bool receiveData();
    extern void ToSend(const unsigned char where, const unsigned int what);
    extern volatile int receiveArray[20];

    extern void RS485_Direction2(int T_L);
#ifdef	__cplusplus
}
#endif

#endif	/* BMMCOMMS_H */

