#include <xc.h>
#include <stdbool.h>
#include "interrupt_handler.h"

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    //INDICATOR3=ON;
    //time++;
    //if(wiiTime<=150) wiiTime++;
    //encoderTime++;

    IFS0bits.T1IF = 0; // clear interrupt flag
    //INDICATOR3=OFF;
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{

    //rolloverRight++;
    //rolloverLeft++;
    IFS0bits.T2IF = 0; // clear timer interrupt flag
}
