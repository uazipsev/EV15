/* 
 * File:   MCSComms.h
 * Author: User
 *
 * Created on June 7, 2015, 7:35 PM
 */

#ifndef MCSCOMMS_H
#define	MCSCOMMS_H

#ifdef	__cplusplus
extern "C" {
#endif


#include "ADDRESSING.h"
#include <stdbool.h>

#define CLOSE_COMM_TIME    4
#define BOARD_TIMEOUT     45
#define BOARD_RESEND_MIN  15

//MCS
    extern volatile unsigned int MCSTimer;

extern unsigned int throttle1,throttle2,brake;

extern void sendData(unsigned char whereToSend);
extern bool receiveData();
extern void ToSend(const unsigned char where, const unsigned int what);
extern volatile int receiveArray[20];

extern void RS485_Direction2(int T_L);
#ifdef	__cplusplus
}
#endif

#endif	/* MCSCOMMS_H */

