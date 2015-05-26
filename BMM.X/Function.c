#include "Function.h"
#include "xc.h"
#include "pps.h"
#include <libpic30.h>
#include "I2C.h"
#include "pwm.h"
#include "CoolingControl.h"
#include "DigiPot.h"


void Setup(void)
{
  // setup internal clock for 66MHz/33MIPS
  // 12/2=6*22=132/2=66
  CLKDIVbits.PLLPRE=0;        // PLLPRE (N2) 0=/2
  PLLFBD=22;                  // pll multiplier (M) = +2
  CLKDIVbits.PLLPOST=0;       // PLLPOST (N1) 0=/2
  while(!OSCCONbits.LOCK);    // wait for PLL ready

  PPSUnLock;

  PPSout (_U1TX,_RP23);
  PPSout (_U2TX,_RP7);
  PPSout (_OC1,_RP5);

  PPSin (_U1RX,_RP22);
  PPSin (_U2RX,_RP6);

  PPSLock;

  i2c_init();
  PinSetMode();
  PotClear();
  PWM_Init();
  CoolingStart();
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
