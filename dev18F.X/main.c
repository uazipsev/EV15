/* 
 * File:   main.c
 * Author: Kilburn
 *
 * Created on February 23, 2015, 11:37 PM
 */

#define _XTAL_FREQ  64000000

 #include <p18cxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "interrupt_manager.h"
#include "initialize.h"
#include "UART.h"
void OSCILLATOR_Initialize(void)
{
    // SCS FOSC; IDLEN disabled; IRCF 16MHz_HFINTOSC/4;
    OSCCON = 0x70;
    // PRISD enabled; MFIOSEL disabled; SOSCGO disabled;
    OSCCON2 = 0x04;
    // INTSRC disabled; PLLEN enabled; TUN 0x00;
    OSCTUNE = 0x40;
    // Set the secondary oscillator

}
void SYSTEM_Initialize(void)
{
    OSCILLATOR_Initialize();
    EUSART1_Initialize();
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
}
void delay(int ms){
    int i=0;
    for(i=0;i<(ms*10);i++)
    {
      Nop();
    }
    return;
}
/*
 * --------------------------------------------------
 *      Important Pins
 * --------------------------------------------------
 *  -- Debug LED    RA3
 *  -- JP10         RA7
 *  -- JP11         RE2
 *  -- JP12         RB5
 *  -- Rx1          RC7
 *  -- Tx1          RC6
 *  -- Rx2          RB7
 *  -- Tx2          RB6
 */
int main(int argc, char** argv) {
    TRISAbits.TRISA3=0;
    SYSTEM_Initialize();
    while(1)
    {
        EUSART1_Write(0x99);
        delay(500);
        LATAbits.LATA3=!LATAbits.LATA3;
        delay(500);
    }


    return (EXIT_SUCCESS);
}

