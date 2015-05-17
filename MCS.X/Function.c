#include "Function.h"
#include "xc.h"
#include "pps.h"
#include <libpic30.h>

#ifndef __DELAY_H
#define FOSC  7372800LL  // clock-frequecy in Hz with suffix LL (64-bit-long), eg. 32000000LL for 32MHz
#define FCY       (FOSC/2)  // MCU is running at FCY MIPS
#define delay_us(x) __delay32(((x*FCY)/1000000L)) // delays x us
#define delay_ms(x) __delay32(((x*FCY)/1000L))  // delays x ms
#define __DELAY_H 1
#include <libpic30.h>
#endif


void Setup(void)
{
  // setup internal clock for 80MHz/40MIPS
  // 7.37/2=3.685*43=158.455/2=79.2275
  //CLKDIVbits.PLLPRE=0;        // PLLPRE (N2) 0=/2
  //PLLFBD=41;                  // pll multiplier (M) = +2
  //CLKDIVbits.PLLPOST=0;       // PLLPOST (N1) 0=/2
  //while(!OSCCONbits.LOCK);    // wait for PLL ready

  PPSUnLock;

  PPSLock;
  TRISBbits.TRISB1 = 0; //Set LED as output
}

void Delay(int wait)
{
    int x;
    for(x = 0;x<wait;x++)
    {
       delay_ms(1);
    }
}
