/* 
 * File:   main.c
 * Author: User
 *
 * Created on March 23, 2015, 8:50 PM
 */
//READABILITY DEFINES
#define INPUT 1
#define OUTPUT 0
#define HIGH 1
#define LOW 0
#define TALK 1
#define LISTEN 0
//OUTPUT COMMAND
#define LEDTRIS TRISBbits.TRISB12
#define L_TTRIS TRISAbits.TRISA9
#define LED LATBbits.LATB12 //SIGN OF LIFE LED
#define DIRECTION485 LATAbits.LATA9 //RS485 DIRECTION

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

#define Rx1_T TRISCbits.TRISC3
#define Tx1_T TRISCbits.TRISC4
#define Rx2_T TRISCbits.TRISC6
#define Tx2_T TRISCbits.TRISC7
#define RxPullup1 LATCbits.LATC3
#define TxPullup1 LATCbits.LATC4
#define RxPullup2 LATCbits.LATC6
#define TxPullup2 LATCbits.LATC7
//UART Definitions
#define U1Rx_RPn RPINR18bits.U1RXR
#define U2Rx_RPn RPINR19bits.U2RXR
#define RP12map RPOR9bits.RP12R
#define RP54map RPOR6bits.RP54R
#define RP20map RPOR10bits.RP20R
#define RP22map RPOR11bits.RP22R
#define RP23map RPOR11bits.RP23R
#define U1Tx_RPn 3
#define U2Tx_RPn 55

//Baud rate generator help
#define BAUDRATE384 38400
#define BAUDRATE96 9600
#define BRGVAL ((FCY/BAUDRATE384)/16)-1
#define BRGVAL2 ((FCY/BAUDRATE96)/16)-1

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <libpic30.h>
#include "system.h"
#include "interrupts.h"

   void initUARTS() {

       Rx1_T=1;
       Tx1_T=1;
       Rx2_T=1;
       Tx2_T=1;
        U2Rx_RPn = 55; //UART2 RX is RP55
        RP54map = U2Tx_RPn; //UART2 TX is RP54

        U1Rx_RPn = 23; //UART1RX  USB
        //RP22map = U1Tx_RPn; //UART1TX USB
        RxPullup1 = 1;
        TxPullup1 = 1;

        RxPullup2 = 1;
        TxPullup2 = 1;
        //----------------- UART1 config ----------------------
        U1BRG = BRGVAL2; // Baud Rate setting for 38400
        U1STAbits.UTXISEL0 = 0, U1STAbits.UTXISEL1 = 0; // Interrupt every character sent out (room for more)
        U1STAbits.URXISEL = 0; // Interrupt after one RX character is received
        U1STAbits.UTXINV = 0;
        IFS0bits.U1TXIF = 0; // Clear the Transmit Interrupt Flag
        //IEC0bits.U1TXIE = 1;	// Enable Transmit Interrupts
        IFS0bits.U1RXIF = 0; // Clear the Recieve Interrupt Flag
        IEC0bits.U1RXIE = 1; // Enable Recieve Interrupts

        U1MODEbits.UARTEN = 1; // Enable UART
        U1STAbits.UTXEN = 1; // Enable UART TX

        //----------------- UART2 config --------------------
        U2MODEbits.STSEL = 0; // 1-Stop bit
        U2MODEbits.PDSEL = 0; // No Parity, 8-Data bits
        U2MODEbits.ABAUD = 0; // Auto-Baud disabled
        U2MODEbits.BRGH = 0; // Standard-Speed mode
        U2BRG = BRGVAL2; // Baud Rate setting for 9600
        U2STAbits.UTXISEL0 = 0, U2STAbits.UTXISEL1 = 0; // Interrupt every character sent out (room for more)
        U2STAbits.URXISEL = 0; // Interrupt after one RX character is received

        IFS1bits.U2TXIF = 0; // Clear the Transmit Interrupt Flag
        //IEC1bits.U2TXIE = 1;	// Enable Transmit Interrupts
        IFS1bits.U2RXIF = 0; // Clear the Recieve Interrupt Flag
        IEC1bits.U2RXIE = 1; // Enable Recieve Interrupts

        U2MODEbits.UARTEN = 1; // Enable UART
        U2STAbits.UTXEN = 1; // Enable UART TX
    }


#define DELAY_100uS asm volatile ("REPEAT, #250"); Nop();
/*
 * 
 */
void delay(int ms){
    int i=0;
    for(i=0;i<(ms*10);i++)
    {
      DELAY_100uS;
    }
    return;
}
int main(int argc, char** argv) {
    ConfigureOscillator();
    initPins();
    TRISBbits.TRISB4=0;
    LATBbits.LATB4=0;
    initUARTS();
    INTCON2bits.GIE=1;
    while(1)
    {
       // LATBbits.LATB4=!LATBbits.LATB4;
        delay(1000);
    }
    
    return (EXIT_SUCCESS);
}

