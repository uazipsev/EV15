#include "xc.h"
#include "pps.h"
#include "PinDef.h"
#include "ADDRESSING.h"
#include <libpic30.h>
#include <stdbool.h>
#include "Functions.h"

extern volatile int receiveArray[20];
extern void PWM_Init(void);

void Setup(void) {

    PinSetMode();
    // setup internal clock for 72MHz/36MIPS
    // 12/2=6*24=132/2=72
    CLKDIVbits.PLLPRE = 0; // PLLPRE (N2) 0=/2
    PLLFBD = 22; // pll multiplier (M) = +2
    CLKDIVbits.PLLPOST = 0; // PLLPOST (N1) 0=/2
    while (!OSCCONbits.LOCK); // wait for PLL ready

    PPSUnLock;
    RX2_Pin_Map = 43;
    RX1_Pin_Map = 48;
    RX3_Pin_Map = 56;
    RX4_Pin_Map = 57;

    Pin_42_Output = TX2_Output;
    Pin_49_Output = TX1_Output;
    Pin_55_Output = TX3_Output;
    Pin_70_Output = TX4_Output;

    PPSout(_OC1, _RP37);
    PPSLock;
    UART_init();
    begin(receiveArray, sizeof (receiveArray), ECU_ADDRESS, false, Send_put, Receive_get, Receive_available, Receive_peek);

    PWM_Init();
}

void Delay(int wait) {
    int x;
    for (x = 0; x < wait; x++) {
        delay_ms(1); //using predef fcn
    }
}

void PinSetMode(void) {
    TRISEbits.TRISE13 = OUTPUT; //Set LED as output
    TRISBbits.TRISB6 = OUTPUT; //Set Brake Light as OUTPUT
    TRISBbits.TRISB5 = OUTPUT; //Set HORN PWM as OUTPUT
    RS485_1_Direction_Tris = OUTPUT;
    RS485_2_Direction_Tris = OUTPUT;
    RS485_1_Direction = LISTEN;
    RS485_2_Direction = LISTEN;

    ANSELCbits.ANSC0=0;
//RX0_Tris=OUTPUT;
//TX0_Tris=OUTPUT;
//RX1_Tris=OUTPUT;
//TX1_Tris=OUTPUT;
//RX_Tris=OUTPUT;
//TX_Tris=OUTPUT;
//RX2_Tris=OUTPUT;
//TX2_Tris=OUTPUT;

}
