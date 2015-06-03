/*
 * File:   Communications.h
 * Author: Zac Kilburn
 *
 * Created on May 31, 2015
 *
 * Handles all of the communications system updates and error checking
 * -- Each board has a turn being communicated with
 *      --If the board doesnt respond, several attemps will be made to retry
 *      --At the end of the communications train there is room to send an error code
 *      --Rs485 direction is automated with packet sends.
 *      --All timers are inside T1 interrupt.. implied approx milliseconds
 */


#include <xc.h>
#include <stdbool.h>
#include "PinDef.h"
#include "ADDRESSING.h"
#include "Communications.h"



void updateComms() {
    checkCommDirection();
    checkCommDirection1();
    bus1Update();
    bus2Update();
}

void bus1Update(){
     switch (commsBus1State) {
        case SAS_UPDATE:
            if (requestSASData()) {
                if (receiveCommSAS()) {
                    commsBus1State++;
                    resetCommTimers();
                }
            } else {
                //FLAG ERROR ON SAS COMMS -- Move on
                SAS_COMMS_ERROR = true;
                commsBus1State++;
                resetCommTimers();
            }
            break;
        case DDS_UPDATE:
            if (requestDDSData()) {
                if (receiveCommDDS()) {
                    commsBus1State++;
                    resetCommTimers();
                }
            } else {
                //FLAG ERROR ON DDS COMMS -- Move on
                DDS_COMMS_ERROR = true;
                commsBus1State++;
                resetCommTimers();
            }
            break;
        case PDU_UPDATE:
            if (requestPDUData()) {
                if (receiveCommPDU()) {
                    commsBus1State++;
                    resetCommTimers();
                }
            } else {
                //FLAG ERROR ON PDU COMMS -- Move on
                PDU_COMMS_ERROR = true;
                commsBus1State++;
                resetCommTimers();
            }
            break;
        case CHECK_STATE1:
            //Before continuing the comms, send to error state if something is wrong
            if (DDS_COMMS_ERROR || SAS_COMMS_ERROR || PDU_COMMS_ERROR) {
                commsBus1State = ERROR_STATE1;
            } else
                //otherwise continue the normal comms update
                commsBus1State = SAS_UPDATE;
            break;
        case ERROR_STATE1:
            sendErrorCode();
            commsBus1State = SAS_UPDATE;
            break;
        case NUM_STATES1:
            break;

    }

}
void bus2Update(){
    switch(commsBus2State){
      case MCS_UPDATE:
            if (requestMCSData()) {
                if (receiveCommMCS()) {
                    commsBus2State++;
                    resetCommTimers2();
                }
            } else {
                //FLAG ERROR ON MCS COMMS -- Move on
                MCS_COMMS_ERROR = true;
                commsBus2State++;
                resetCommTimers2();
            }
            break;
        case CHECK_STATE2:
            if (MCS_COMMS_ERROR) {
                commsBus2State = ERROR_STATE2;
            } else
                //otherwise continue the normal comms update
                commsBus2State = MCS_UPDATE;
            break;
        case ERROR_STATE2:
            sendErrorCode2();
            commsBus2State=MCS_UPDATE;
            break;
        case NUM_STATES2:
            break;
    }
}

//  Error Code Handling
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
    if (PDU_COMMS_ERROR) {
        errorState = errorState | 0x04;
        PDU_COMMS_ERROR = false;
    }
    ToSend2(BUS_1_ERROR_DEBUG, errorState);
    sendData2(DEBUG_ADDRESS);
}
void sendErrorCode2() {
    unsigned int errorState = 0;   
    if (MCS_COMMS_ERROR) {
        errorState = errorState | 0x01;
        MCS_COMMS_ERROR = false;
    }
    ToSend2(BUS_2_ERROR_DEBUG, errorState);
    sendData2(DEBUG_ADDRESS);
}

//  Timer Resets Per Bus
void resetCommTimers() {
    SASTimer = 0;
    DDSTimer = 0;
    PDUTimer = 0;
}
void resetCommTimers2() {
    MCSTimer = 0;
}
bool requestSASData() {
    //If either timeout or response with delay already occured
    if (((SASTimer > 50) && (readyToSendSAS)) || (SASTimer > 100)) {
        static int SASErrorCounter = 0;
        if (!readyToSendSAS) {
            SASErrorCounter++;
            if (SASErrorCounter > 5) {
                SASErrorCounter = 0;
                return false;
            }
        } else {
            readyToSendSAS = false;
            SASErrorCounter = 0;
        }
        SASTimer = 0;
        RS485_Direction1(TALK);
        ToSend1(RESPONSE_ADDRESS, ECU_ADDRESS);
        sendData1(SAS_ADDRESS);
    }

    return true;
}
bool receiveCommSAS() {
    if (receiveData1()) {
        if (receiveArray1[RESPONSE_ADDRESS] == SAS_ADDRESS) {
            readyToSendSAS = true;
            SASTimer = 0;
            return true;
        } else return false;
    } else return false;
}

bool requestDDSData() {
    if (((DDSTimer > 50) && (readyToSendDDS)) || (DDSTimer > 100)) {
        static int DDSErrorCounter = 0;
        if (!readyToSendDDS) {
            DDSErrorCounter++;
            if (DDSErrorCounter > 5) {
                DDSErrorCounter = 0;
                return false;
            }
        } else {
            readyToSendDDS = false;
            DDSErrorCounter = 0;
        }
        ToSend1(RESPONSE_ADDRESS, ECU_ADDRESS);
        ToSend1(LED_DDS, indicators);
        RS485_Direction1(TALK);
        sendData1(DDS_ADDRESS);
        DDSTimer = 0;
    }
    return true;

}

bool receiveCommDDS() {
    if (receiveData1()) {
        if (receiveArray1[RESPONSE_ADDRESS] == DDS_ADDRESS) {
            buttons=receiveArray1[BUTTONS_DDS];
            readyToSendDDS = true;
            DDSTimer = 0;
            return true;
        } else return false;
    } else return false;
}


bool requestMCSData() {
   if (((MCSTimer > 50) && (readyToSendMCS)) || (MCSTimer > 100)) {
        static int MCSErrorCounter = 0;
        if (!readyToSendMCS) {
            MCSErrorCounter++;
            if (MCSErrorCounter > 5) {
                MCSErrorCounter = 0;
                return false;
            }
        } else {
            readyToSendMCS = false;
            MCSErrorCounter = 0;
        }
        RS485_Direction2(TALK);
        ToSend(RESPONSE_ADDRESS, ECU_ADDRESS);
        sendData(MCS_ADDRESS);
        MCSTimer = 0;
    }
    return true;
}

bool receiveCommMCS() {
    if (receiveData()) {
        if (receiveArray[RESPONSE_ADDRESS] == MCS_ADDRESS) {
            readyToSendMCS = true;
            MCSTimer = 0;
            return true;
        } else return false;
    } else return false;
    return true;
}

bool requestPDUData() {
    if (((PDUTimer > 50) && (readyToSendPDU)) || (PDUTimer > 100)) {
        static int PDUErrorCounter = 0;
        if (!readyToSendPDU) {
            PDUErrorCounter++;
            if (PDUErrorCounter > 5) {
                PDUErrorCounter = 0;
                return false;
            }
        } else {
            PDUErrorCounter = 0;
            readyToSendPDU = false;
        }
        PDUTimer = 0;
        RS485_Direction1(TALK);
        ToSend1(RESPONSE_ADDRESS, ECU_ADDRESS);
        sendData1(PDU_ADDRESS);
    }
    return true;
}

bool receiveCommPDU() {
    if (receiveData1()) {
        if (receiveArray1[RESPONSE_ADDRESS] == PDU_ADDRESS) {
            readyToSendPDU = true;
            PDUTimer = 0;
            return true;
        } else return false;
    } else return false;
}


void checkCommDirection() {   
    //you have finished send and time has elapsed.. start listen
    if (Transmit_stall && (talkTime > 2)) {
        RS485_Direction1(LISTEN);
    }
}

void checkCommDirection1() {
    //you have finished send and time has elapsed.. start listen
    if (Transmit_stall1 && (talkTime1 > 2)) {
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