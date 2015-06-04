#include <xc.h>
#include <stdbool.h>
#include "interrupt_handler.h"
#include "PinDef.h"
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    LEDtime++;
    talkTime++;
    IFS0bits.T1IF = 0; // clear interrupt flag
}

//    if(ADCTime>10){
//        IEC0bits.AD1IE =1;
//        ADCTime=0;
//    }else ADCTime++;
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {
    //LED^=1;
    IFS0bits.T2IF = 0; // clear timer interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void) {
    static int ADC = 0;
    if (!ADCDataReady) {
        ADCbuffer[ADC] = ADC1BUF0;
        ADC++;
    }
    if (ADC > 6) {
        ADCDataReady = 1;
        ADC = 0;
        IEC0bits.AD1IE = 0;
        AD1CHS0bits.CH0SA = 0;
        return;
    }
    AD1CHS0bits.CH0SA = ADC;
    AD1CON1bits.DONE = 0;
    AD1CON1bits.SAMP = 1;

    IFS0bits.AD1IF = 0; // clear ADC interrupt flag
}

