/* 
 * File:   PinDef.h
 * Author: Rick
 *
 * Created on May 12, 2015, 12:00 AM
 */

#ifndef PINDEF_H
#define	PINDEF_H

/*
 *  RS485 Flow control
 */
#define RS_RE_DE _LATB0

/*
 *    LED :)
 */
#define INDICATOR _LATB9

#define startByte 0xEC
#define stopByte 0x99
#define address 0x01

//some constant declarations
#define numSlaves 28
#define LEDT 2000 //200 counts of 5ms till LED toggle (~1 second)
#define ST 8 //50 counts of 5ms for slave retransmit (~250 ms)

//Baud rate generator help
#define FP 12500000
#define BAUDRATE384 38400
#define BAUDRATE96 9600
#define BRGVAL ((FP/BAUDRATE384)/16)-1
#define BRGVAL2 ((FP/BAUDRATE96)/16)-1

//READABILITY DEFINES
#define INPUT 1
#define OUTPUT 0
#define HIGH 1
#define LOW 0
#define TALK 1
#define LISTEN 0
#define true 1
#define false 0
//OUTPUT COMMAND

#define RxPullup1 LATCbits.LATC3
#define TxPullup1 LATCbits.LATC4
#define RxPullup2 LATCbits.LATC6
#define TxPullup2 LATCbits.LATC7
//UART Definitions
#define U1Rx_RPn RPINR18bits.U1RXR
#define U2Rx_RPn RPINR19bits.U2RXR
#define RP12map RPOR6bits.RP12R
#define RP19map RPOR9bits.RP19R
#define RP20map RPOR10bits.RP20R
#define RP22map RPOR11bits.RP22R
#define RP23map RPOR11bits.RP23R
#define U1Tx_RPn 3
#define U2Tx_RPn 5


#endif	/* PINDEF_H */

