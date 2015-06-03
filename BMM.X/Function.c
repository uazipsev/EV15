#include <xc.h>
#include <libpic30.h>
#include <stdbool.h>
#include "Function.h"
#include "pps.h"
#include "pwm.h"
#include "PinDef.h"
#include "ADDRESSING.h"

void Setup(void)
{
  // setup internal clock for 72MHz/36MIPS
  // 12 /2 = 6  *24 = 144 / 2=72
  CLKDIVbits.PLLPRE = 0; // PLLPRE (N2) 0=/2c
  CLKDIVbits.DOZE=0;
  PLLFBD = 22; // pll multiplier (M) = +2
  CLKDIVbits.PLLPOST = 0; // PLLPOST (N1) 0=/2
  while (!OSCCONbits.LOCK); // wait for PLL ready

  PPSUnLock;

  PPSout (_U2TX,_RP7);
  PPSout (_OC1,_RP5);

  PPSin (_U2RX,_RP6);

    Pin_24_Output = TX1_OUTPUT;
    RX1_Pin_Map = 25;
  PPSLock;
  
  UART_init();
  begin(receiveArray, sizeof (receiveArray), BMM_ADDRESS, false, Send_put, Receive_get, Receive_available, Receive_peek);
  
  i2c_init();
  PinSetMode();
  PWM_Init();
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
    TRISBbits.TRISB1  = 0; //Set LED as output

    TRISBbits.TRISB5  = 0;  //Fan control OUT
    
    TRISBbits.TRISB13 = 0; // RS485 Direction Pin OUTPUT
    LATBbits.LATB13   = 0;
}
