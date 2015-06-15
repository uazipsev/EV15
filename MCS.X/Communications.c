#include "Communications.h"
#include "MotorControler.h"
int throttleOut = 0, brakeOut = 0;
bool pendingSend = false;
bool portClosed = true;

void commSafety();
void updateComms() {
    checkCommDirection();
    if (receiveData()) {
        static bool carActive = false;
        carActive=receiveArray[OUTPUT_ACTIVE];
        if (carActive) {
            if(!PORTAbits.RA10){
                LATAbits.LATA10=1;
            }
             if(!PORTAbits.RA0){
                 LATAbits.LATA0=1;
             }
            if (throttleOut != receiveArray[THROTTLE_OUTPUT]) {
                throttleOut = receiveArray[THROTTLE_OUTPUT];
                SetMotor(throttleOut, 1);
            }
            if (brakeOut != receiveArray[BRAKE_OUTPUT]) {
                brakeOut = receiveArray[BRAKE_OUTPUT];
                SetRegen(brakeOut);
            }
        }
        else{
            if(brakeOut!=0){
                brakeOut=0;
                SetRegen(0);
            }
            if(throttleOut!=0){
                throttleOut=0;
                SetMotor(0,1);
            }
            LATAbits.LATA0=0;
            LATAbits.LATA10=0;
        }
        talkTime = 0;
        safetyTime = 0;
        pendingSend = true;
    }
    if (pendingSend && portClosed && talkTime > 5) {
        talkTime = 0;
        portClosed = false;
        RS485_1_Port = TALK;
    }
    if (pendingSend && talkTime > 1 && !portClosed) {
        talkTime = 0;
        respondECU();
        pendingSend = false;
    }
    commSafety();
}

void commSafety() {
    if (safetyTime > 200) {
        SetMotor(0, 1);
        SetRegen(0);
        LATAbits.LATA10=0;
            LATAbits.LATA0=0;
    }
}

void respondECU() {
    ToSend(RESPONSE_ADDRESS, MCS_ADDRESS);
    sendData(ECU_ADDRESS);
    talkTime = 0;
}

void checkCommDirection() {
    //you have finished send and time has elapsed.. start listen
    if (Transmit_stall && (talkTime > 5) && (RS485_1_Port == TALK)) {
        RS485_1_Port = LISTEN;
        portClosed = true;
    }
}
