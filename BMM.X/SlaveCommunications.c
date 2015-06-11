#include "SlaveCommunications.h"

void sendSlavePacket(int slave);
int BVolts[NUMSLAVES][BATTPERSLAVE];
int BTemps[NUMSLAVES][TEMPPERSLAVE];
int faultCount[NUMSLAVES];
bool pendingSend1 = true;
void updateSlaveCommunications();
void checkSlaveCommDirection();

void updateSlaveCommunications() {
    static int slaveaddr;

    if (pendingSend1 && slaveTime > 15) {
        slaveTime = 0;
        sendSlavePacket(slaveaddr);
        pendingSend1 = false;
    }
    if (receiveData1()) {
        static bool wrongReturn = false;
        //Received when expecting it
        if (!pendingSend1) {
            if (slaveaddr == receiveArray1[RESPONSE_ADDRESS]) {
                //----------------- Handle the faulting -----------------
                if (receiveArray1[BATTERYFAULT]) {
                    faultCount[slaveaddr] = NUM_FAILS_TO_FAULT + 1;
                }
                faultCount[slaveaddr] = 0;
                wrongReturn = false;
                //-----------------   Store the data  -----------------
                int i = 0;
                for (i = 0; i < BATTPERSLAVE; i++) {
                    BVolts[slaveaddr][i] = receiveArray1[BATTERYV + i];
                }
                for (i = 0; i < BATTPERSLAVE; i++) {
                    BTemps[slaveaddr][i] = receiveArray1[BATTERYT + i];
                }
                //Increment to the next slave
                slaveaddr++;
            }//Else you heard from the wrong address -- try a resend
            else if (!wrongReturn) {
                wrongReturn = true;
                pendingSend1 = true;
            } else {
                //Addressing issue (twice you heard from the wrong address)
                slaveaddr++;
                wrongReturn = false;
                //FAULT?
            }

            slaveTime = 0;
            pendingSend1 = true;
            RS485_SLAVE_Port = !TALK;
            RS485_SLAVE_Port1 = !TALK;
        } else {
            //Received when not expecting it
            //FAULT?
        }
    } else {
        //You didnt receive after sending
        if (!pendingSend1) {
            if (slaveTime > 50) { //if timed out
                slaveTime = 0; //reset timer
                pendingSend1 = true; //set to send to the next slave
                int i = 0;
                for (i = 0; i < BATTPERSLAVE; i++) { //wipe current slave data to indicate a loss
                    BVolts[slaveaddr][i] = 0;
                    BTemps[slaveaddr][i] = 0;
                }
                faultCount[slaveaddr]++;
                if (faultCount[slaveaddr] >= NUM_FAILS_TO_FAULT) {
                    //FAULT?
                }
                if (slaveaddr < NUMSLAVES - 1)
                    slaveaddr++;
                else slaveaddr = 0;
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
    if (Transmit_stall1 && (slaveTime > 10) && ((RS485_SLAVE_Port == !TALK) || (RS485_SLAVE_Port1 == !TALK))) {
        RS485_SLAVE_Port = !LISTEN;
        RS485_SLAVE_Port1 = !LISTEN;
    }
}