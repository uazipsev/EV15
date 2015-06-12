#include "SlaveCommunications.h"
#include "PinDef.h"
void sendSlavePacket(int slave);
int BVolts[NUMSLAVES][BATTPERSLAVE];
int BTemps[NUMSLAVES][TEMPPERSLAVE];
int faultCount[NUMSLAVES];
bool pendingSend1 = true, portTalk = false;
void updateSlaveCommunications();
void checkSlaveCommDirection();

void updateSlaveCommunications() {
    static int slaveaddr = 1;

    if (pendingSend1 && slaveTime > 11 && !portTalk) {
        RS485_SLAVE_Port = !TALK;
        RS485_SLAVE_Port1 = !TALK;
        portTalk = true;
    }
    if (pendingSend1 && slaveTime > 15 && portTalk) {
        sendSlavePacket(slaveaddr);
        pendingSend1 = false;
        slaveTime = 0;
    }


    if (receiveData1()) {

        INDICATOR = !INDICATOR;
        static bool wrongReturn = false;
        //Received when expecting it
        //        if (!pendingSend1) {
        //if (slaveaddr == receiveArray1[RESPONSE_ADDRESS]) {
        //----------------- Handle the faulting -----------------
        if (receiveArray1[BATTERYFAULT]) {
            faultCount[slaveaddr-1] = NUM_FAILS_TO_FAULT + 1;
        }
        faultCount[slaveaddr-1] = 0;
        wrongReturn = false;
        //-----------------   Store the data  -----------------
        int i = 0;
        for (i = 0; i < BATTPERSLAVE; i++) {
            BVolts[receiveArray1[RESPONSE_ADDRESS]][i] = receiveArray1[BATTERYV + i];
        }
        for (i = 0; i < BATTPERSLAVE; i++) {
            BTemps[receiveArray1[RESPONSE_ADDRESS]][i] = receiveArray1[BATTERYT + i];
        }
        //Increment to the next slave
        if (slaveaddr < NUMSLAVES1) {
            slaveaddr++;
        } else if (slaveaddr == NUMSLAVES1) {
            slaveaddr++;
            //send to slave set 2
            //S1 = 0;
        } else if (slaveaddr < NUMSLAVES) {
            slaveaddr++;
        } else {
            slaveaddr = 1;
            //Back to slave set 1
            S1 = 1;
        }
        //            }//Else you heard from the wrong address -- try a resend
        //            else if (!wrongReturn) {
        //                wrongReturn = true;
        //                pendingSend1 = true;
        //            } else {
        //                //Addressing issue (twice you heard from the wrong address)
        //                slaveaddr++;
        //                wrongReturn = false;
        //                //FAULT?
        //            }

        slaveTime = 0;
        pendingSend1 = true;
        //        } else {
        //            //Received when not expecting it
        //            //FAULT?
        //        }
    } else {
        //You didnt receive after sending
        if (!pendingSend1) {
            if (slaveTime > 50) { //if timed out
                slaveTime = 0; //reset timer
                pendingSend1 = true; //set to send to the next slave
                int i = 0;
                for (i = 0; i < BATTPERSLAVE; i++) { //wipe current slave data to indicate a loss
                    BVolts[slaveaddr-1][i] = 0;
                    BTemps[slaveaddr-1][i] = 0;
                }
                faultCount[slaveaddr-1]++;
                if (faultCount[slaveaddr-1] >= NUM_FAILS_TO_FAULT) {
                    //FAULT?
                }
                //Increment to the next slave
                if (slaveaddr < NUMSLAVES1) {
                    slaveaddr++;
                } else if (slaveaddr == NUMSLAVES1) {
                    slaveaddr++;
                    //send to slave set 2
                    //S1 = 0;
                } else if (slaveaddr < NUMSLAVES) {
                    slaveaddr++;
                } else {
                    slaveaddr = 1;
                    //Back to slave set 1
                    S1 = 1;
                }
            }
        }
    }

}

void sendSlavePacket(int slave) {
    slaveTime = 0;
    ToSend1(RESPONSE_ADDRESS, BMM_ADDRESS);
    sendData1(slave);
}

void checkSlaveCommDirection() {
    //you have finished send and time has elapsed.. start listen
    if (Transmit_stall1 && (slaveTime > 3) && ((RS485_SLAVE_Port == !TALK) || (RS485_SLAVE_Port1 == !TALK)) && !pendingSend1 && portTalk) {
        RS485_SLAVE_Port = !LISTEN;
        RS485_SLAVE_Port1 = !LISTEN;
        portTalk = false;
    }
}