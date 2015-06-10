#include "debug.h"
#include <stdio.h>
#include "ADDRESSING.h"

enum debugStates debugState;
extern int DDS_FAULT_CONDITION, MCS_FAULT_CONDITION, SAS_FAULT_CONDITION, BMM_FAULT_CONDITION, PDU_FAULT_CONDITION, ECU_FAULT_CONDITION;
extern int milliVolts[16];
extern int temps[16];
extern int current1, current2, bigVolts;
void handleDebugRequests();

int write(int handle, void *buffer, unsigned int len) {
    int i;
    switch (handle) {
        case 0: // handle 0 corresponds to stdout
        case 1: // handle 1 corresponds to stdin
        case 2: // handle 2 corresponds to stderr
        default:
            for (i = 0; i < len; i++)
                Send_put2(*(char*) buffer++);
    }
    return (len);
}

void handleDebugRequests() {
    if (DebugTimer > 1000) {
        switch (debugState) {
            case NO_DEBUG:
                break;
            case THROTTLE_BRAKE:
                printf("\nThrottle1:      %d\n", throttle1);
                printf("Throttle2:      %d\n", throttle2);
                printf("Brake:          %d\n\n", brake);
                break;
            case BATTERY_DEBUG_VOLTS:
                printf("\nB1: %dV B2: %dV B3: %dV B4: %dV  \n", milliVolts[0], milliVolts[1], milliVolts[2], milliVolts[3]);
                printf("B5: %dV B6: %dV B7: %dV B8: %dV  \n", milliVolts[4], milliVolts[5], milliVolts[6], milliVolts[7]);
                printf("B9: %dV B10:%dV B11:%dV B12:%dV  \n", milliVolts[8], milliVolts[9], milliVolts[10], milliVolts[11]);
                printf("B13:%dV B14:%dV B15:%dV B16:%dV  \n\n", milliVolts[12], milliVolts[13], milliVolts[14], milliVolts[15]);
                break;
            case BATTERY_DEBUG_TEMPS:
                printf("\nB1:  %dF B2:  %dF B3:  %dF B4:  %dF  \n", temps[0], temps[1], temps[2], temps[3]);
                printf("B5:  %dF B6:  %dF B7:  %dF B8:  %dF  \n", temps[4], temps[5], temps[6], temps[7]);
                printf("B9:  %dF B10: %dF B11: %dF B12: %dF  \n", temps[8], temps[9], temps[10], temps[11]);
                printf("B13: %dF B14: %dF B15: %dF B16: %dF  \n\n", temps[12], temps[13], temps[14], temps[15]);
                break;
            case BATTERY_DEBUG_POWER:
                printf("\nCurrent Pack 1:  %d\n", current1);
                printf("Current Pack 2:  %d\n", current2);
                printf("HV pack voltage: %d\n", bigVolts);
                break;
            case FAULT_RECOVERY:
                if(MCS_FAULT_CONDITION){

                }
                if(BMM_FAULT_CONDITION){

                }
                if(SAS_FAULT_CONDITION){

                }
                if(DDS_FAULT_CONDITION){

                }
                if(PDU_FAULT_CONDITION){

                }
                if(ECU_FAULT_CONDITION){

                }
                break;
            case NUM_DEBUG_STATES:
                break;
        }
        DebugTimer = 0;
    }

    if (receiveData2()) {
        ToSend2(RESPONSE_ADDRESS, ECU_ADDRESS);
        sendData2(DEBUG_ADDRESS);
    }

}