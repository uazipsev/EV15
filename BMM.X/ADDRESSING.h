/* 
 * File:   ADDRESSING.h
 * Author: Zac Kilburn
 *
 * Created on May 27, 2015, 5:35 PM
 */

#ifndef ADDRESSING_H
#define	ADDRESSING_H

#ifdef	__cplusplus
extern "C" {
#endif


    //Addresses
#define ECU_ADDRESS 1
#define SAS_ADDRESS 2
#define DDS_ADDRESS 3
#define MCS_ADDRESS 4
#define PDU_ADDRESS 5

    //ECU Data
#define RESPONSE_ADDRESS        0
#define THROTTLE1               1
#define THROTTLE2               2
#define BRAKE                   3
#define WHEELSPEED1             4
#define WHEELSPEED2             5
#define WHEELSPEED3             6
#define WHEELSPEED4             7

    //MCS Receive
#define THROTTLE_OUTPUT         1
#define BRAKE_OUTPUT            2

    //PDU Receive
#define POWER_RAILS             1

    //SAS Receive
#define SIGNAL_REQUEST          1
#define WHEELSPEED_REQUEST      2

    //DDS Receive
#define BUTTON_REQUEST          1




#define DEBUG_ADDRESS 9

#define ERRORS 1

#ifdef	__cplusplus
}
#endif

#endif	/* ADDRESSING_H */

