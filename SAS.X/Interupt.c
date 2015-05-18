#include <xc.h>

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    //INDICATOR3=ON;
    //time++;
    //if(wiiTime<=150) wiiTime++;
    //encoderTime++;

    IFS0bits.T1IF = 0; // clear interrupt flag
    //INDICATOR3=OFF;
}