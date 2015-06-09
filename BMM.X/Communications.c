
#include "Communications.h"

extern volatile unsigned int slaveTime;
void sendSlavePacket();
void updateComms() {
    checkCommDirection();
    if (receiveData()) {
        talkTime = 0;
        pendingSend = true;
        RS485_Port = TALK;
    }
    if (pendingSend && talkTime > 5) {
        talkTime = 0;
        ToSend(RESPONSE_ADDRESS, BMM_ADDRESS);
        sendData(ECU_ADDRESS);
        pendingSend = false;
    }
    if(slaveTime>10){
        slaveTime=0;
        sendSlavePacket();
    }
}

void sendSlavePacket(){
    ToSend1(RESPONSE_ADDRESS,BMM_ADDRESS);
    sendData1(1);
}
void checkCommDirection() {
    //you have finished send and time has elapsed.. start listen
    if (Transmit_stall && (talkTime > 15) && (RS485_Port == TALK)) {
        RS485_Port = LISTEN;
    }
}