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
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "PinDef.h"
#include "ADDRESSING.h"
#include "Communications.h"
#include "SASComms.h"
#include "MCSComms.h"
#include "DDSComms.h"
#include "PDUComms.h"
#include "BMMComms.h"


void updateComms() {
    static bool startup = false;
    if (!startup) {
        setbuf(stdout, NULL);
        startup = true;
    }
    checkCommDirection();
    checkCommDirection1();
    bus1Update();
    bus2Update();
}

void bus1Update() {
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
void checkCommDirection() {
    //you have finished send and time has elapsed.. start listen
    if (Transmit_stall && (talkTime > CLOSE_COMM_TIME)) {
        RS485_Direction1(LISTEN);
    }
}
void resetCommTimers() {
    SASTimer = 0;
    DDSTimer = 0;
    PDUTimer = 0;
}
void RS485_Direction1(int T_L) {
    RS485_1_Direction = T_L;
    talkTime = 0;

}
void sendErrorCode() {
    unsigned int errorState = 0;
    if (DDS_COMMS_ERROR) {
        errorState = errorState | 0x01;
        DDS_COMMS_ERROR = false;
        //printf("DDS Communications Error \r\n");
    }
    if (SAS_COMMS_ERROR) {
        errorState = errorState | 0x02;
        SAS_COMMS_ERROR = false;
        //printf("SAS Communications Error \r\n");
    }
    if (PDU_COMMS_ERROR) {
        errorState = errorState | 0x04;
        PDU_COMMS_ERROR = false;
        //printf("PDU Communications Error \r\n");
    }

    //ToSend2(BUS_1_ERROR_DEBUG, errorState);
    //sendData2(DEBUG_ADDRESS);
}

void bus2Update() {
    switch (commsBus2State) {
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
        case BMM_UPDATE:
            if (requestBMMData()) {
                if (receiveCommBMM()) {
                    commsBus2State++;
                    resetCommTimers2();
                }
            } else {
                //FLAG ERROR ON MCS COMMS -- Move on
                BMM_COMMS_ERROR = true;
                commsBus2State++;
                resetCommTimers2();
            }
            break;
        case CHECK_STATE2:
            if (MCS_COMMS_ERROR || BMM_COMMS_ERROR) {
                commsBus2State = ERROR_STATE2;
            } else
                //otherwise continue the normal comms update
                commsBus2State = MCS_UPDATE;
            break;
        case ERROR_STATE2:
            sendErrorCode2();
            commsBus2State = MCS_UPDATE;
            break;
        case NUM_STATES2:
            break;
    }
}
void checkCommDirection1() {
    if (!Transmit_stall1) talkTime1 = 0;
    //you have finished send and time has elapsed.. start listen
    if (Transmit_stall1 && (talkTime1 > CLOSE_COMM_TIME)) {
        RS485_Direction2(LISTEN);
    }
}
void resetCommTimers2() {
    MCSTimer = 0;
    BMMTimer = 0;
}
void RS485_Direction2(int T_L) {
    RS485_2_Direction = T_L;
    talkTime1 = 0;

}
void sendErrorCode2() {
    unsigned int errorState = 0;
    if (MCS_COMMS_ERROR) {
        errorState = errorState | 0x01;
        MCS_COMMS_ERROR = false;
    }
    if (BMM_COMMS_ERROR) {
        errorState = errorState | 0x02;
        BMM_COMMS_ERROR = false;
    }
    //debugSAS();
    //ToSend2(BUS_2_ERROR_DEBUG, errorState);
    //sendData2(DEBUG_ADDRESS);
}




//Debug interface for printf
extern void Send_put2(unsigned char _data);
extern unsigned char Receive_get2(void);

char getch(void) {
    return Receive_get2();
}

void putch(char txData) {
    Send_put2(txData);
}

//void _mon_putc(char c){
//    Send_put2(c);
//}