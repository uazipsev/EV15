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


/*
 *    Relay control 
 */
#define Analog_Relay _LATA0

#define startByte 0xEC
#define stopByte 0x99
#define address 0x01

//asm delay function -- should work :)
#define DELAY_100uS asm volatile ("REPEAT, #2500"); Nop();
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
#define false 0
//OUTPUT COMMAND
#define LEDTRIS TRISBbits.TRISB12
#define L_TTRIS TRISAbits.TRISA9
#define LED LATBbits.LATB12 //SIGN OF LIFE LED
#define L_T LATAbits.LATA9 //RS485 DIRECTION

#define AN0 TRISAbits.TRISA0
#define AN1 TRISAbits.TRISA1
#define AN2 TRISCbits.TRISC0
#define AN3 TRISBbits.TRISB2
#define AN4 TRISBbits.TRISB3
#define AN5 TRISCbits.TRISC1

#define AN0L LATAbits.LATA0
#define AN1L LATAbits.LATA1
#define AN2L LATCbits.LATC0
#define AN3L LATBbits.LATB2
#define AN4L LATBbits.LATB3
#define AN5L LATCbits.LATC1

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

#define Speed1 24
#define Speed2 25
#define Speed3 10
#define Speed4 11

#define T2Clock RPINR3bits.T2CKR
#define T3Clock RPINR3bits.T3CKR
#define T4Clock RPINR4bits.T4CKR
#define T5Clock RPINR4bits.T5CKR

#define BrakeLight LATAbits.LATA4

//INTERRUPT0 pin config
#define Interrupt0Pin RPINR0bits.INT1R



#endif	/* PINDEF_H */

