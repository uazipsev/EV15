#include "Functions.h"
#include <xc.h>
#include <stdbool.h>
#include "Global.h"
#include "ADC.h"
#include "PinDef.h"
#include "pps.h"

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
  //begin(receiveArray, 15, 1, false, Send_put, Receive_get, Receive_available, Receive_peek);
  //INDICATOR4=ON;
  //UART_init();
  //initUART1();
  //initADC();
  //timerOne();
  //timerTwo();
  //GLOBAL_INTERRUPTS = 1;
}

//void timerOne(void)
//{
//
//    T1CONbits.TCKPS = 0b10; // 64 divider
//    PR1 = 938; // 0.001s timer
//    IPC0bits.T1IP = 1; // interrupt priority level 1
//    IFS0bits.T1IF = 0; // clear interrupt flag
//    IEC0bits.T1IE = 1; // enable timer 1 interrupt
//    T1CONbits.TON = 1; // turn on timer
//}
//
//void timerTwo(void)
//{
//        // timer 2
//    T2CONbits.TON = 0; //disable timer 2
//    T2CONbits.TCS = 0; //internal instruction clock (60,000,000 Hertz)
//    T2CONbits.TGATE = 0; //disable gated timer mode
//    T2CONbits.TCKPS = 0b11; // 1:256 prescalar    60MHz/256= 234.375KHz (4.266us)
//    TMR2 = 0x00; //clar timer register
//    PR2 = 65535; //- set to 279 ms per overflow (4.266 us * 65535)= 279 ms
//    IPC1bits.T2IP = 0x01; // timer lowest priority level
//    IFS0bits.T2IF = 0; // clear timer1 interrupt flag
//    IEC0bits.T2IE = 0; // disable timer1 interrupt
//    T2CONbits.TON = 1; //enable timer 2
//}

void initUART1(void)
{
    U1MODEbits.BRGH = 0; // 16 multiplier
    U1BRG = 64; // 57600 baud rate
    U1MODEbits.UARTEN = 1; // enable uart
}

//void inputCapture(void)
//{
//    // Initialize the Input Capture Module
//    IC1CON1bits.ICM = 0b00; // Disable Input Capture 1 module
//    IC1CON1bits.ICTSEL= 1; // Select Timer2 as the IC1 Time base
//    IC1CON1bits.ICI = 0b00; // Interrupt on every capture event
//    IC1CON1bits.ICM = 0b010; // Generate capture event on every Falling edge
//
//    // Enable Capture Interrupt And Timer2
//    IPC0bits.IC1IP = 1; // Setup IC1 interrupt priority level
//    IFS0bits.IC1IF = 0; // Clear IC1 Interrupt Status Flag
//    IEC0bits.IC1IE = 1; // Enable IC1
//
//    //pin remap
//    RPINR7bits.IC1R = 98; // right tread
//
//    // Initialize the Input Capture Module
//    IC2CON1bits.ICM = 0b00; // Disable Input Capture 2 module
//    IC2CON1bits.ICTSEL = 1; // Select Timer2 as the IC2 Time base
//    IC2CON1bits.ICI = 0b00; // Interrupt on every capture event
//    IC2CON1bits.ICM = 0b010; // Generate capture event on every Falling edge
//
//    // Enable Capture Interrupt And Timer2
//    IPC1bits.IC2IP = 1; // Setup IC2 interrupt priority level
//    IFS0bits.IC2IF = 0; // Clear IC2 Interrupt Status Flag
//    IEC0bits.IC2IE = 1; // Enable IC2
//
//    //pin remap
//    RPINR7bits.IC2R = 99; // left tread
//}

void PinSetMode(void)
{
      LED_Port = 0;  // LED indicator OUT
      RS485_Port = 0; //RS485 Flow OUT
}


void Delay(int wait)
{
    int x = 0;
    for(;x<wait;x++)
    {
        delay_ms(1);
    }
}