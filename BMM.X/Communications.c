
#include "Communications.h"
#include "SlaveCommunications.h"

enum BMM {
    BATTERY_FAULT = 0,
    BATTERY_VOLTS = 1,
    BATTERY_TEMPS = 2,
    BATTERY_POWER = 3
} COMM_STATE;
int faultFlag = 0;
int slaveaddr = 0;
bool portClosed = false;

void updateComms() {
    checkSlaveCommDirection();
    updateSlaveCommunications();
    if (receiveData()) {
        talkTime = 0;
        COMM_STATE = receiveArray[BMM_COMM_STATE];
        pendingSend = true;
    }
    if (!portClosed && pendingSend && talkTime > 5) {
        RS485_Port = TALK;
        portClosed = true;
    }
    if (pendingSend && talkTime > 6 && portClosed) {
        ToSend(RESPONSE_ADDRESS, BMM_ADDRESS);
        static int lastCommState = 0;
        switch (COMM_STATE) {
            case BATTERY_VOLTS:
                if (lastCommState != COMM_STATE) {
                    lastCommState = COMM_STATE;
                    slaveaddr = 0;
                }
                populateBatteryV(slaveaddr++);
                if (slaveaddr >= NUMSLAVES) slaveaddr = 0;
                break;
            case BATTERY_TEMPS:
                if (lastCommState != COMM_STATE) {
                    lastCommState = COMM_STATE;
                    slaveaddr = 0;
                }
                populateBatteryT(slaveaddr++);
                if (slaveaddr >= NUMSLAVES) slaveaddr = 0;
                break;
            case BATTERY_POWER:
                if (lastCommState != COMM_STATE) {
                    lastCommState = COMM_STATE;
                }
                break;
            case BATTERY_FAULT:
                if (lastCommState != COMM_STATE) {
                    lastCommState = COMM_STATE;
                }
                break;

            default:
                break;

        }
        ToSend(BMM_FAULT, faultFlag);
        switch (faultFlag) {
            case 1:
            case 2:
            case 3:
            default:
                break;
        }
        sendData(ECU_ADDRESS);
        pendingSend = false;

        talkTime = 0;
    }
    checkCommDirection();
}

void checkCommDirection() {
    //you have finished send and time has elapsed.. start listen
    if (Transmit_stall && (talkTime > 12) && (RS485_Port == TALK) && portClosed && !pendingSend) {
        RS485_Port = LISTEN;
        portClosed = false;
    }
}

void populateBatteryT(int slave) {
    ToSend(SLAVE_ADDRESS_SEND, slave);
    int j = 0;
    for (j = 0; j < BATTPERSLAVE; j++) {
        ToSend(BATTERYT_ECU + j, BTemps[slave][j]);
    }
}

void populateBatteryV(int slave) {
    ToSend(SLAVE_ADDRESS_SEND, slave);
    int j = 0;
    for (j = 0; j < BATTPERSLAVE; j++) {
        ToSend(BATTERYV_ECU + j, BVolts[slave][j]);
    }
}

