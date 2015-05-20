#include "Functions.h"
#include "PinDef.h"
#include "UART.h"
#include "ADC.h"
#include "FastTransfer.h"
#include "Global.h"
#include "pps.h"
#include <xc.h>

void Setup(void)
{
    // Disable Watch Dog Timer
    RCONbits.SWDTEN = 0;
    //set up clock
    CLKDIVbits.PLLPRE=0;        // PLLPRE (N2) 0=/2
    PLLFBD=22;                  // pll multiplier (M) = +2
    CLKDIVbits.PLLPOST=0;       // PLLPOST (N1) 0=/2
    while(!OSCCONbits.LOCK);    // wait for PLL ready
    
    PPSUnLock;

    TRISAbits.TRISA4=0;

    U2Rx_RPn = 20; //UART2 RX is RP19 for ECU bus
    RP19map = U2Tx_RPn; //UART2 TX isRP20 for ECU bus

    RxPullup1 = 1;
    TxPullup1 = 1;

    RxPullup2 = 1;
    TxPullup2 = 1;

    PPSLock;

    initADC();
    initInterrupts();
    begin(receiveArray, 15, 1, false, Send_put, Receive_get, Receive_available, Receive_peek);
    UART_init();
}

void Delay(int wait)
{
    int x;
    for(x = 0;x<wait;x++)
    {
       delay_ms(1);
    }
}

void initInterrupts(void)
{
    INTCON1bits.NSTDIS = 1; //no nesting of interrupts
    IFS0bits.U1TXIF = 0;
    IFS1bits.U2TXIF = 0;
    IFS0bits.U1RXIF = 0;
    IFS1bits.U2RXIF = 0;
}

void initGPIO(void)
{
    TRISBbits.TRISB9 = 0; //Set LED as output
}
