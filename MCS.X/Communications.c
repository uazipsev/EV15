#include "Communications.h"
#include "MotorControler.h"
int throttleOut=0, brakeOut=0;
bool pendingSend=false;
void updateComms() {
    checkCommDirection();
    if (receiveData()) {
        throttleOut = receiveArray[THROTTLE_OUTPUT];
        brakeOut    = receiveArray[BRAKE_OUTPUT];
        SetMotor(throttleOut,1);
        SetRegen(brakeOut);        
        talkTime    = 0;
        pendingSend = true;
    }
    if (pendingSend && talkTime > 50) {
        RS485_1_Port = TALK;
        talkTime = 0;
        respondECU();
        pendingSend = false;
    }
}

void respondECU() {
    ToSend(RESPONSE_ADDRESS, MCS_ADDRESS);
    sendData(ECU_ADDRESS);
    talkTime=0;

}

void checkCommDirection() {
    //you have finished send and time has elapsed.. start listen
    if (Transmit_stall && (talkTime > 150) && (RS485_1_Port == TALK)) {
        RS485_1_Port = LISTEN;
    }
}
