#include "PDUComms.h"
bool requestPDUData();
bool receiveCommPDU();
bool readyToSendPDU = true;
bool PDU_COMMS_ERROR = false;
bool requestPDUData() {
    if (((PDUTimer > BOARD_RESEND_MIN) && (readyToSendPDU)) || (PDUTimer > BOARD_TIMEOUT)) {
        static int PDUErrorCounter = 0;
        if (!readyToSendPDU) {
            PDUErrorCounter++;
            if (PDUErrorCounter > 1) {
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
