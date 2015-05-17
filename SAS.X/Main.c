/* 
 * File:   Main.c
 * Author: Richard Johnson
 *
 * Created on May 16, 2015, 11:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#define INDICATOR _LATB9

#ifndef __DELAY_H
#define FOSC  7372800LL  // clock-frequecy in Hz with suffix LL (64-bit-long), eg. 32000000LL for 32MHz
#define FCY       (FOSC/2)  // MCU is running at FCY MIPS
#define delay_us(x) __delay32(((x*FCY)/1000000L)) // delays x us
#define delay_ms(x) __delay32(((x*FCY)/1000L))  // delays x ms
#define __DELAY_H 1
#include <libpic30.h>
#endif

void Delay(int wait);
/*
 * 
 */
int main(int argc, char** argv) {
    TRISBbits.TRISB9 = 0; //Set LED as output
    INDICATOR = 1;
    int i;
    while(1)
    {
        /*
        for(i =0;i<32;i++)
        {
           //PotSetpoint(i);
           Delay(250);
           INDICATOR = !INDICATOR;
        }
        */
        Delay(250);
       INDICATOR = 1;
        Delay(250);
       INDICATOR = 0;
       Delay(250);
    }
    return (EXIT_SUCCESS);
}


void Delay(int wait)
{
    int x;
    for(x = 0;x<wait;x++)
    {
       delay_ms(1);
    }
}
