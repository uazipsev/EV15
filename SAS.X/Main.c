
#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "PinDef.h"
#include "main.h"
#include "ADDRESSING.h"

void checkCommDirection();
int main(void) {
    Setup();
    LED = 0;
    Delay(500);
    while (1) {
        ledDebug();
         
        //Comms handling
        if (receiveData()) {
            //if(receiveArray[RESPONSE_ADDRESS]==ECU_ADDRESS){
            Delay(5);
            prepAndSendData();
            //}
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
    //you are sending data, make sure tunnel is open
        if (!Transmit_stall) {
            talkTime = 0;
            //RS485_1_Port = TALK;
        }
        //you have finished send and time has elapsed.. start listen
        if (Transmit_stall && (talkTime > 3) && (PORTCbits.RC8==TALK)) {
            RS485_1_Port = LISTEN;
        }


}
void prepAndSendData() {
    static int sender;
    ToSend(RESPONSE_ADDRESS, SAS_ADDRESS);
    ToSend(THROTTLE1, sender++);
    ToSend(THROTTLE2, sender++);
    ToSend(BRAKE, sender++);
    ToSend(WHEELSPEED1, sender++);
    ToSend(WHEELSPEED2, sender++);
    ToSend(WHEELSPEED3, sender++);
    ToSend(WHEELSPEED4, sender++);
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
