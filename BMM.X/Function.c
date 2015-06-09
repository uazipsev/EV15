
#include "Function.h"

void Setup(void) {
    PinSetMode();
    // setup internal clock for 72MHz/36MIPS
    // 12 /2 = 6  *24 = 144 / 2=72
    CLKDIVbits.PLLPRE = 0; // PLLPRE (N2) 0=/2c
    CLKDIVbits.DOZE = 0;
    PLLFBD = 22; // pll multiplier (M) = +2
    CLKDIVbits.PLLPOST = 0; // PLLPOST (N1) 0=/2
    while (!OSCCONbits.LOCK); // wait for PLL ready


    INTCON1bits.NSTDIS = 1; //no nesting of interrupts

    PPSUnLock;
    PPSout(_OC1, _RP5);
    Pin_24_Output = TX1_OUTPUT;
    RX1_Pin_Map = 25;
    Pin_22_Output = TX2_OUTPUT;
    RX2_Pin_Map = 23;
    PPSLock;
    UART_init();
    begin(receiveArray, sizeof (receiveArray), BMM_ADDRESS, false, Send_put, Receive_get, Receive_available, Receive_peek);
    UART1_init();
    begin1(receiveArray1, sizeof (receiveArray1), BMM_ADDRESS, false, Send_put1, Receive_get1, Receive_available1, Receive_peek1);

    
    
    initTimerOne();

    initTimerTwo();
    //i2c_init();
    //PWM_Init();
}

void Delay(int wait) {
    int x;
    for (x = 0; x < wait; x++) {
        delay_ms(1); //using predif fcn
    }
}

void PinSetMode(void) {
    AD1PCFGL = 0XFFFF;
    TRISBbits.TRISB1 = OUTPUT; //Set LED as output

    TRISBbits.TRISB5 = OUTPUT; //Fan control OUT

    TRISBbits.TRISB13 = OUTPUT; // RS485 Direction Pin OUTPUT
    LATBbits.LATB13 = 0;
    
    TRISCbits.TRISC7 = 1;
    LATCbits.LATC7=1;
    
    S0_TRIS=OUTPUT;     //Select Comm Line Mux S0
    S1_TRIS=OUTPUT;     //Select Comm Line Mux S1
    S0 =0;
    S1 =1;
    
}
