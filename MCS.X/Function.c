#include "Function.h"
#include "xc.h"
#include "pps.h"
#include <libpic30.h>

#ifndef __DELAY_H
#define FOSC  66000000LL  // clock-frequecy in Hz with suffix LL (64-bit-long), eg. 32000000LL for 32MHz
#define FCY       (FOSC/2)  // MCU is running at FCY MIPS
#define delay_us(x) __delay32(((x*FCY)/1000000L)) // delays x us
#define delay_ms(x) __delay32(((x*FCY)/1000L))  // delays x ms
#define __DELAY_H 1
#include <libpic30.h>
#endif


void Setup(void)
{
  // setup internal clock for 66MHz/33MIPS
  // 12/2=6*22=132/2=66
  CLKDIVbits.PLLPRE=0;        // PLLPRE (N2) 0=/2
  PLLFBD=22;                  // pll multiplier (M) = +2
  CLKDIVbits.PLLPOST=0;       // PLLPOST (N1) 0=/2
  while(!OSCCONbits.LOCK);    // wait for PLL ready

  PPSUnLock;

  PPSLock;

  PinSetMode();
  PotClear();
}

void Delay(int wait)
{
    int x;
    for(x = 0;x<wait;x++)
    {
       delay_ms(1);  //using predif fcn
    }
}

void PinSetMode(void)
{
    TRISBbits.TRISB1 = 0; //Set LED as output
    TRISAbits.TRISA0 = 0; //DAC relay OUT
    TRISAbits.TRISA10 = 0; //Set 12v DC/DC enable OUT

    TRISBbits.TRISB15 = 0; //DigiPot CS OUT
    TRISBbits.TRISB14 = 0; //DigiPot INC OUT
    TRISAbits.TRISA7 = 0;  //DigiPot UP_DN OUT

    TRISBbits.TRISB5 = 0;  //Fan control OUT
}
