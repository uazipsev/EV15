#include <xc.h>
#include <stdbool.h>
#include "initialize.h"

#define ON         0
#define OFF        1
#define INDICATOR1 LATEbits.LATE5
#define INDICATOR2 LATEbits.LATE6
#define INDICATOR3 LATGbits.LATG7
#define INDICATOR4 LATGbits.LATG8
#define WATCHDOG   LATEbits.LATE7

#define GLOBAL_INTERRUPTS  INTCON2bits.GIE
#define SOFTWARE_TRAP INTCON2bits.SWTRAP
void initialize(void)
{

    ANSELEbits.ANSE5  = 0; // turn off analog
    TRISEbits.TRISE5  = 0; // RE5 set to output
    ANSELEbits.ANSE6  = 0; // turn off analog
    TRISEbits.TRISE6  = 0; // RE6 set to output
    ANSELEbits.ANSE7  = 0; // turn off analog
    TRISEbits.TRISE7  = 0; // RE7 set to output
    ANSELGbits.ANSG7  = 0; // turn off analog
    TRISGbits.TRISG7  = 0; // RG7 set to output
    ANSELGbits.ANSG8  = 0; // turn off analog
    TRISGbits.TRISG8  = 0; // RG8 set to output
    INTCON1bits.NSTDIS= 0;
    GLOBAL_INTERRUPTS = 0;
    oscillator();
    INDICATOR1=ON;
    InitI2Cone();
    InitI2Ctwo();
    INDICATOR2=ON;
    initPWM1(0);
    initPWM2(0);
    INDICATOR3=ON;
    begin(receiveArray, 15, 1, false, Send_put, Receive_get, Receive_available, Receive_peek);
    INDICATOR4=ON;
    UART_init();

    INDICATOR1=OFF;
    INDICATOR2=OFF;
    INDICATOR3=OFF;
    INDICATOR4=OFF;
    //initUART1();
    timerOne();
    timerTwo();
    INDICATOR3=ON;
    inputCapture();


    INDICATOR1=OFF;
    INDICATOR2=OFF;
    INDICATOR3=OFF;
    INDICATOR4=OFF;
    GLOBAL_INTERRUPTS = 1;
    
}

void oscillator(void)
{
    // 120MHz 60MIPS
    // Configure PLL prescaler, PLL postscaler, PLL divisor
    PLLFBD = 58; // M=60
    CLKDIVbits.PLLPOST = 0; // N2=2
    CLKDIVbits.PLLPRE = 4; // N1=6

    // Initiate Clock Switch to PRI oscillator with PLL (NOSC=0b011)
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(OSCCON | 0x01);

    // Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b011);
    //    // Wait for PLL to lock
    while (OSCCONbits.LOCK != 1);
}

void timerOne(void)
{

    T1CONbits.TCKPS = 0b10; // 64 divider
    PR1 = 938; // 0.001s timer
    IPC0bits.T1IP = 1; // interrupt priority level 1
    IFS0bits.T1IF = 0; // clear interrupt flag
    IEC0bits.T1IE = 1; // enable timer 1 interrupt
    T1CONbits.TON = 1; // turn on timer
}

void timerTwo(void)
{
        // timer 2
    T2CONbits.TON = 0; //disable timer 2
    T2CONbits.TCS = 0; //internal instruction clock (60,000,000 Hertz)
    T2CONbits.TGATE = 0; //disable gated timer mode
    T2CONbits.TCKPS = 0b11; // 1:256 prescalar    60MHz/256= 234.375KHz (4.266us)
    TMR2 = 0x00; //clar timer register
    PR2 = 65535; //- set to 279 ms per overflow (4.266 us * 65535)= 279 ms
    IPC1bits.T2IP = 0x01; // timer lowest priority level
    IFS0bits.T2IF = 0; // clear timer1 interrupt flag
    IEC0bits.T2IE = 0; // disable timer1 interrupt
    T2CONbits.TON = 1; //enable timer 2
}

void initUART1(void)
{

    RPINR18bits.U1RXR = 66; // RP66 for RX
    RPOR0bits.RP65R = 1;
    U1MODEbits.BRGH = 0; // 16 multiplier
    U1BRG = 64; // 57600 baud rate
    U1MODEbits.UARTEN = 1; // enable uart
}

void inputCapture(void)
{
    // Initialize the Input Capture Module
    IC1CON1bits.ICM = 0b00; // Disable Input Capture 1 module
    IC1CON1bits.ICTSEL= 1; // Select Timer2 as the IC1 Time base
    IC1CON1bits.ICI = 0b00; // Interrupt on every capture event
    IC1CON1bits.ICM = 0b010; // Generate capture event on every Falling edge

    // Enable Capture Interrupt And Timer2
    IPC0bits.IC1IP = 1; // Setup IC1 interrupt priority level
    IFS0bits.IC1IF = 0; // Clear IC1 Interrupt Status Flag
    IEC0bits.IC1IE = 1; // Enable IC1

    //pin remap
    RPINR7bits.IC1R = 98; // right tread

    // Initialize the Input Capture Module
    IC2CON1bits.ICM = 0b00; // Disable Input Capture 2 module
    IC2CON1bits.ICTSEL = 1; // Select Timer2 as the IC2 Time base
    IC2CON1bits.ICI = 0b00; // Interrupt on every capture event
    IC2CON1bits.ICM = 0b010; // Generate capture event on every Falling edge

    // Enable Capture Interrupt And Timer2
    IPC1bits.IC2IP = 1; // Setup IC2 interrupt priority level
    IFS0bits.IC2IF = 0; // Clear IC2 Interrupt Status Flag
    IEC0bits.IC2IE = 1; // Enable IC2

    //pin remap
    RPINR7bits.IC2R = 99; // left tread
}