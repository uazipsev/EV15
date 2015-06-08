#include "BMMComms.h"
bool requestBMMData();
bool receiveCommBMM();
bool readyToSendBMM = true;
bool BMM_COMMS_ERROR = false;
bool requestBMMData() {
    if (((BMMTimer > BOARD_RESEND_MIN) && (readyToSendBMM)) || (BMMTimer > BOARD_TIMEOUT)) {
        static int BMMErrorCounter = 0;
        if (!readyToSendBMM) {
            BMMErrorCounter++;
            if (BMMErrorCounter > 1) {
                BMMErrorCounter = 0;
                return false;
            }
        } else {
            BMMErrorCounter = 0;
            readyToSendBMM = false;
        }
        BMMTimer = 0;
        RS485_Direction2(TALK);
        ToSend(RESPONSE_ADDRESS, ECU_ADDRESS);
        sendData(BMM_ADDRESS);
    }
    return true;
}

bool receiveCommBMM() {
    if (receiveData()) {
        if (receiveArray[RESPONSE_ADDRESS] == BMM_ADDRESS) {
            readyToSendBMM = true;
            BMMTimer = 0;
            return true;
        } else return false;
    } else return false;
}
