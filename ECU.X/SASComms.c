#include "SASComms.h"

bool receiveCommSAS();
bool requestSASData();
bool readyToSendSAS = true;
bool SAS_COMMS_ERROR = false;

void debugSAS() {
    ToSend2(5, throttle1);
    ToSend2(6, throttle2);
    ToSend2(7, brake);
    sendData2(DEBUG_ADDRESS);

}

bool requestSASData() {
    //If either timeout or response with delay already occurred
    if (((SASTimer > BOARD_RESEND_MIN) && (readyToSendSAS)) || (SASTimer > BOARD_TIMEOUT)) {
        static int SASErrorCounter = 0;
        if (!readyToSendSAS) {
            SASErrorCounter++;
            if (SASErrorCounter > 1) {
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

bool checkSASInputs(unsigned int t1, unsigned int t2, unsigned int b) {
    //throttle consistency check
    if (!((t1 + (t1 / 10) > t2) && (t1 - (t1 / 10) < t2))) {
        return false;
    }
    //Brake vs. throttle safety
    if (((t1 + t2 / 2) > TRIP_THROTTLE) && (b > TRIP_BRAKE)) {
        return false;
    }
    return true;
}

bool receiveCommSAS() {
    if (receiveData1()) {
        if (receiveArray1[RESPONSE_ADDRESS] == SAS_ADDRESS) {
            if (checkSASInputs(throttle1, throttle2, brake)) {
                throttle1 = receiveArray1[THROTTLE1_SAS];
                throttle2 = receiveArray1[THROTTLE2_SAS];
                brake = receiveArray1[BRAKE_SAS];
            }
            readyToSendSAS = true;
            SASTimer = 0;
            return true;
        } else return false;
    } else return false;
}
