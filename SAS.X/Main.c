
#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "PinDef.h"
#include "main.h"
#include "ADDRESSING.h"

int main(void) {
    Setup();
    LED = 0;
    Delay(500);
    while (1) {
        ledDebug();
        
        if (ADCDataReady) {
            ADCDataReady = false;
            handleADCValues();
            IEC0bits.AD1IE = 1;
            //LED ^= 1;
        }
        //Comms handling
        if (receiveData()) {
            if (receiveArray[RESPONSE_ADDRESS] == ECU_ADDRESS) {
                Delay(5);
                prepAndSendData();
            }
        }
        checkCommDirection();
    }
}

void ledDebug() {
    if (LEDtime > 1000) {
        LED ^= 1;
        LEDtime = 0;
    }
}

void checkCommDirection() {
    //you have finished send and time has elapsed.. start listen
    if (Transmit_stall && (talkTime > 10) && (PORTCbits.RC8 == TALK)) {
        RS485_1_Port = LISTEN;
        talkTime=0;
    }
}

void prepAndSendData() {
    static int sender;
    ToSend(RESPONSE_ADDRESS, SAS_ADDRESS);
    ToSend(THROTTLE1_SAS, throttle1);
    ToSend(THROTTLE2_SAS, throttle2);
    ToSend(BRAKE_SAS, brake);
    ToSend(WHEELSPEED1_SAS, sender++);
    ToSend(WHEELSPEED2_SAS, sender++);
    ToSend(WHEELSPEED3_SAS, sender++);
    ToSend(WHEELSPEED4_SAS, sender++);
    //    ToSend(8, sender++);
    //    ToSend(9, sender++);
    //    ToSend(10, sender++);
    //    ToSend(11, sender++);
    //    ToSend(12, sender++);
    //    ToSend(13, sender++);
    talkTime = 0;
    RS485_1_Port = TALK;
    sendData(ECU_ADDRESS);

}
