#include "Functions.h"
#include "PinDef.h"
#include "UART.h"
#include "ADC.h"
#include "FastTransfer.h"
#include "Global.h"
#include <xc.h>

void Setup(void)
{
    // Disable Watch Dog Timer
    RCONbits.SWDTEN = 0;
    //CLKDIV=(CLKDIV &0xFFE5);
    //PLLFBD=12;
    OSCCONbits.NOSC = 2;
    OSCCONbits.OSWEN = 1;
    //IO lock (unlock)
    OSCCON = 0x46;
    OSCCON = 0x57;
    OSCCONbits.IOLOCK = 0;
    AD1PCFGL = 0xFF0C; //configure the analog pins to digital

    LEDTRIS = OUTPUT;
    L_TTRIS = OUTPUT;
    TRISAbits.TRISA4=0;
    AN0 = 1;
    AN1 = 1;
    AN2 = 1;
    AN3 = 1;
    AN4 = 1;
    AN5 = 1;

    LED = HIGH;

    U2Rx_RPn = 20; //UART2 RX is RP19 for ECU bus
    RP19map = U2Tx_RPn; //UART2 TX isRP20 for ECU bus

    U1Rx_RPn = 23; //UART1RX  USB
    RP22map = U1Tx_RPn; //UART1TX USB
    L_T = LISTEN;
    RxPullup1 = 1;
    TxPullup1 = 1;

    RxPullup2 = 1;
    TxPullup2 = 1;

    OSCCON = 0x46;
    OSCCON = 0x57;
    OSCCONbits.IOLOCK = 1;
    //IO lock (lock)
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
