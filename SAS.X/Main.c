
#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "PinDef.h"
#include "main.h"
#include "ADDRESSING.h"

int main(void) {
    Setup();
    LED = 0;
    
    while (1) {
        ledDebug();
        //Comms handling
        if (receiveData()) {
            Delay(5);
            prepAndSendData();
        }
        //you are sending data, make sure tunnel is open
        if (!Transmit_stall) {
            talkTime = 0;
            RS485_1_Port = TALK;
        }
        //you have finished send and time has elapsed.. start listen
        if (Transmit_stall && (talkTime > 2)) {
            RS485_1_Port = LISTEN;
        }
    }
}

void ledDebug() {
    if (LEDtime > 1000) {
        LED ^= 1;
        LEDtime = 0;
    }
}

void prepAndSendData() {
    static int sender;
    ToSend(THROTTLE1, sender++);
    ToSend(THROTTLE2, sender++);
    ToSend(BRAKE, sender++);
    ToSend(WHEELSPEED1, sender++);
    ToSend(WHEELSPEED2, sender++);
    ToSend(WHEELSPEED3, sender++);
    ToSend(WHEELSPEED4, sender++);
    ToSend(8, sender++);
    ToSend(9, sender++);
    ToSend(10, sender++);
    ToSend(11, sender++);
    ToSend(12, sender++);
    ToSend(13, sender++);

    RS485_1_Port = TALK;
    talkTime = 0;
    sendData(ECU_ADDRESS);


}
