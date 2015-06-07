
#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "PinDef.h"
#include "main.h"
#include "ADDRESSING.h"

int main(void) {
    Setup();
    LED = 1;   
    while (1) {
        ledDebug();
        //Comms handling
        updateComms();
                if (ADCDataReady) {
                    ADCDataReady = false;
                    handleADCValues();
                    IEC0bits.AD1IE = 1;
                    //ADCTime=0;
                    //ADCSamp=false;
                }
//                if((!ADCSamp) && (!ADCDataReady)){// && (ADCTime>0)){
//                    IEC0bits.AD1IE = 1;
//                    AD1CON1bits.SAMP = 1;
//                    ADCSamp=true;
//                    ADCTime=0;
//                }
    }
}


