/* 
 * File:   PDUComms.h
 * Author: User
 *
 * Created on June 7, 2015, 7:35 PM
 */

#ifndef PDUCOMMS_H
#define	PDUCOMMS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "ADDRESSING.h"
#include <stdbool.h>

#define CLOSE_COMM_TIME    4
#define BOARD_TIMEOUT     45
#define BOARD_RESEND_MIN  15
    extern volatile unsigned int PDUTimer;

    extern void sendData1(unsigned char whereToSend);
    extern bool receiveData1();
    extern void ToSend1(const unsigned char where, const unsigned int what);
    extern volatile int receiveArray1[20];

    extern void RS485_Direction1(int T_L);
#ifdef	__cplusplus
}
#endif

#endif	/* PDUCOMMS_H */
