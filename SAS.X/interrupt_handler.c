#include <xc.h>
#include <stdbool.h>
#include "interrupt_handler.h"
#include "PinDef.h"

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    LEDtime++;
    talkTime++;
    IFS0bits.T1IF = 0; // clear interrupt flag
}
extern volatile unsigned int ADCTime;
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {
    ADCTime++;
    IFS0bits.T2IF = 0; // clear timer interrupt flag
}


