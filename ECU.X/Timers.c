#include <xc.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Timers.h"

void initTimerOne(){
    T1CONbits.TON = 0; // turn off timer
    T1CONbits.TCS = 0;
    T1CONbits.TCKPS = 0;  //0b10 - 64 divider
    PR1 = 37500; // 0.001s timer
    IFS0bits.T1IF = 0; // clear interrupt flag
    IEC0bits.T1IE = 1; // enable timer 1 interrupt
    T1CONbits.TON = 1; // turn on timer
}


void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    time++;
    talkTime++;
    talkTime1++;
    talkTime2++;
    talkTime3++;
    SASTimer++;
    DDSTimer++;
    MCSTimer++;
    BootTimer++;
    IFS0bits.T1IF = 0; // clear interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{

    IFS0bits.T2IF = 0; // clear timer interrupt flag
}
