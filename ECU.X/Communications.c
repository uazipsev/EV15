#include <xc.h>
#include <stdbool.h>
#include "PinDef.h"
#include "ADDRESSING.h"
#include "Communications.h"


void resetCommTimers() {
    SASTimer = 0;
    DDSTimer = 0;
    MCSTimer = 0;
    PDUTimer = 0;
}

void updateComms() {

    checkCommDirection();
    checkCommDirection1();

    switch (commsState) {
        case SAS_UPDATE:
            if (requestSASData()) {
                if (receiveCommSAS()) {
                    commsState++;
                    resetCommTimers();
                }
            } else {
                //FLAG ERROR ON SAS COMMS -- Move on
                SAS_COMMS_ERROR = true;
                commsState++;
                resetCommTimers();
            }
            break;
        case DDS_UPDATE:
            if (requestDDSData()) {
                if (receiveCommDDS()) {
                    commsState++;
                    resetCommTimers();
                }
            } else {
                //FLAG ERROR ON DDS COMMS -- Move on
                DDS_COMMS_ERROR = true;
                commsState++;
                resetCommTimers();
            }
            break;
        case CHECK_STATE:
            //Before continuing the comms, send to error state if something is wrong
            if (DDS_COMMS_ERROR || SAS_COMMS_ERROR || MCS_COMMS_ERROR) {
                commsState = ERROR_STATE;
            } else
                //otherwise continue the normal comms update
                commsState = SAS_UPDATE;
            break;
        case ERROR_STATE:
            INDICATOR = 1;
            sendErrorCode();
            commsState = SAS_UPDATE;
            
            break;

    }
}

void sendErrorCode() {
    unsigned int errorState = 0;
    if (DDS_COMMS_ERROR) {
        errorState = errorState | 0x01;
        DDS_COMMS_ERROR = false;
    }
    if (SAS_COMMS_ERROR) {
        errorState = errorState | 0x02;
        SAS_COMMS_ERROR = false;
    }
    if (MCS_COMMS_ERROR) {
        errorState = errorState | 0x04;
        MCS_COMMS_ERROR = false;
    }
    ToSend2(ERRORS, errorState);
    sendData2(DEBUG_ADDRESS);
}

void receiveComm() {
    if (receiveData1()) {
        BRAKELT ^= 1;
        readyToSendSAS = true;
        SASTimer = 0;
    }
}

void receiveComm1() {
    if (receiveData()) {
        RTD(100);
    }
}

bool receiveCommSAS() {
    if (receiveData1()) {
        if (receiveArray1[RESPONSE_ADDRESS] == SAS_ADDRESS) {
            BRAKELT ^= 1;
            readyToSendSAS = true;
            SASTimer = 0;
            return true;
        } else return false;
    } else return false;

}

bool receiveCommDDS() {
    if (receiveData1()) {
        if (receiveArray1[RESPONSE_ADDRESS] == DDS_ADDRESS) {
            BRAKELT ^= 1;
            readyToSendDDS = true;
            DDSTimer = 0;
            return true;
        } else return false;
    } else return false;

}

bool requestDDSData() {
    if (((DDSTimer > 50) && (readyToSendDDS)) || (DDSTimer > 100)) {


        if (!readyToSendDDS) {
            static int DDSErrorCounter = 0;
            DDSErrorCounter++;
            if (DDSErrorCounter > 5) {
                DDSErrorCounter = 0;
                return false;
            }
        } else readyToSendDDS = false;

        RS485_Direction1(TALK);
        ToSend1(RESPONSE_ADDRESS, ECU_ADDRESS);
        sendData1(DDS_ADDRESS);
        DDSTimer = 0;
    }
    return true;

}

void requestMCSData() {


}

void requestPDUData() {


}

bool requestSASData() {
    if (((SASTimer > 50) && (readyToSendSAS)) || (SASTimer > 100)) {


        if (!readyToSendSAS) {
            static int SASErrorCounter = 0;
            SASErrorCounter++;
            if (SASErrorCounter > 5) {
                SASErrorCounter = 0;
                return false;
            }
        } else readyToSendSAS = false;
        SASTimer = 0;
        RS485_Direction1(TALK);
        ToSend1(RESPONSE_ADDRESS, ECU_ADDRESS);
        sendData1(SAS_ADDRESS);
    }

    return true;
}

void checkCommDirection() {
    //you are sending data, make sure tunnel is open
    if (!Transmit_stall) {
        RS485_Direction1(TALK);
    }
    //you have finished send and time has elapsed.. start listen
    if (Transmit_stall && (talkTime > 3)) {
        RS485_Direction1(LISTEN);
    }
}

void checkCommDirection1() {
    //you are sending data, make sure tunnel is open
    if (!Transmit_stall1) {
        RS485_Direction2(TALK);
    }
    //you have finished send and time has elapsed.. start listen
    if (Transmit_stall1 && (talkTime1 > 3)) {
        RS485_Direction2(LISTEN);
    }
}

void RS485_Direction1(int T_L) {
    RS485_1_Direction = T_L;
    talkTime = 0;

}

void RS485_Direction2(int T_L) {
    RS485_2_Direction = T_L;
    talkTime1 = 0;

}