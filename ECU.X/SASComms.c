#include "SASComms.h"

unsigned int throttle1, throttle2, brake;
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
//    if (!((t1 + (t1 / 10) > t2) && (t1 - (t1 / 10) < t2))) {
//        return false;
//    }
//    //Brake vs. throttle safety
//    if (((t1 + t2 / 2) > TRIP_THROTTLE) && (b > TRIP_BRAKE)) {
//        return false;
//    }
    return true;
}
void storeSASInputs(){
    float brakemV, throttle1mV, throttle2mV;
    
    throttle1mV = (receiveArray1[THROTTLE1_SAS] / 4095.0)*3300.0;
    throttle2mV = (receiveArray1[THROTTLE2_SAS] / 4095.0)*3300.0;
    brakemV     = (receiveArray1[BRAKE_SAS] / 4095.0)*3300.0;

    if (throttle1mV < 2200.0 && throttle1mV > 1200.0){ 
        throttle1 = (throttle1mV-1300.0) * (100.0 / 800.0);
        if(throttle1<0) throttle1=0;
        if(throttle1>100) throttle1=100;
    } else throttle1 = 0;
    if (brakemV < 2700.0 && brakemV > 1000.0) {
        brake = (brakemV-1200.0) * (100.0 / 1650.0);
        if(brake<0) brake=0;
        if(brake>100) brake=100;
    } else brake = 0;
    
}

bool receiveCommSAS() {
    if (receiveData1()) {
        if (receiveArray1[RESPONSE_ADDRESS] == SAS_ADDRESS) {
            if (checkSASInputs(throttle1, throttle2, brake)) {
                storeSASInputs();                
            }
            readyToSendSAS = true;
            SASTimer = 0;
            return true;
        } else return false;
    } else return false;
}
