#include "Function.h"
#include "xc.h"
#include "pps.h"

void Setup(void)
{
  // setup internal clock for 80MHz/40MIPS
  // 7.37/2=3.685*43=158.455/2=79.2275
  CLKDIVbits.PLLPRE=0;        // PLLPRE (N2) 0=/2
  PLLFBD=41;                  // pll multiplier (M) = +2
  CLKDIVbits.PLLPOST=0;       // PLLPOST (N1) 0=/2
  while(!OSCCONbits.LOCK);    // wait for PLL ready

  PPSUnLock;

  PPSLock;
}

void Delay(int wait)
{

}
