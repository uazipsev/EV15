#include <xc.h>
#include <stdbool.h>
#include "interrupt_handler.h"
#include "PinDef.h"

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    LEDtime++;
    talkTime++;
    IFS0bits.T1IF = 0; // clear interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {
    ADCTime++;
    IFS0bits.T2IF = 0; // clear timer interrupt flag
}
int ADC = 0;
void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void) {
//    if (!ADCDataReady) {
//        ADCbuffer[ADC] = ADC1BUF0;
//        ADC++;
//        ADCSamp=false;
//        ADCTime=0;
//        IEC0bits.AD1IE = 0;
//    }
//    if (ADC > 6) {
//        ADCTime=0;
//        ADCDataReady = 1;
//        ADC = 0;
//        ADCSamp=true;
//    }
//    AD1CHS0bits.CH0SA = ADC;

    IFS0bits.AD1IF = 0; // clear ADC interrupt flag
}

