#include "BMMComms.h"
#include "SlaveAddressing.h"
extern int BMM_FAULT_CONDITION;

enum BMM {
    BATTERY_FAULT = 0,
    BATTERY_VOLTS = 1,
    BATTERY_TEMPS = 2,
    BATTERY_POWER = 3
};

struct commsStates {
    bool DDS;
    bool MCS;
    bool SAS;
    bool BMM;
    bool PDU;
    int DDS_SEND;
    int MCS_SEND;
    int SAS_SEND;
    enum BMM BMM_SEND;
    int PDU_SEND;
};

int milliVolts[NUMSLAVES][BATTPERSLAVE];
int temps[NUMSLAVES][BATTPERSLAVE];
int current1, current2, bigVolts;
int faultingBattery;
bool batteryFault = false;
bool requestBMMData(struct commsStates * cS);
bool receiveCommBMM();
bool readyToSendBMM = true;
bool BMM_COMMS_ERROR = false;

bool requestBMMData(struct commsStates * cS) {
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

        switch ((*cS).BMM_SEND) {
            case BATTERY_FAULT:
                ToSend(BMM_COMM_STATE, 0);
                break;
            case BATTERY_VOLTS:
                ToSend(BMM_COMM_STATE, 1);
                break;
            case BATTERY_TEMPS:
                ToSend(BMM_COMM_STATE, 2);
                break;
            case BATTERY_POWER:
                ToSend(BMM_COMM_STATE, 3);
                break;
        }
        ToSend(RESPONSE_ADDRESS, ECU_ADDRESS);
        sendData(BMM_ADDRESS);
    }
    return true;
}

bool receiveCommBMM(struct commsStates * cS) {
    int j;
    if (receiveData()) {
        if (receiveArray[RESPONSE_ADDRESS] == BMM_ADDRESS) {
            switch ((*cS).BMM_SEND) {
                case BATTERY_FAULT:
                    if (receiveArray[BATTERYFAULT]) {
                        batteryFault = true;
                        faultingBattery = (receiveArray[SLAVE_ADDRESS_SEND] * BATTPERSLAVE) + receiveArray[FAULTINGBATTERY];
                    }
                    break;
                case BATTERY_VOLTS:
                    for (j = 0; j < BATTPERSLAVE; j++)
                        milliVolts[receiveArray[SLAVE_ADDRESS_SEND]][j] = receiveArray[BATTERYV + j];
                    break;
                case BATTERY_TEMPS:
                    for (j = 0; j < BATTPERSLAVE; j++)
                        temps[receiveArray[SLAVE_ADDRESS_SEND]][j] = receiveArray[BATTERYV + j];
                    break;
                case BATTERY_POWER:

                    break;
            }
            readyToSendBMM = true;
            BMMTimer = 0;
            return true;
        } else return false;
    } else return false;
}
