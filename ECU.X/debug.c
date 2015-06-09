#include "debug.h"
#include <stdio.h>
#include "ADDRESSING.h"
void handleDebugRequests();
int milliVolts[50];
int temps[50];
int current1, current2, bigVolts;
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

void handleDebugRequests(int state) {
    if (DebugTimer > 1000) {
        switch (state){
            case NO_DEBUG:
                break;
            case THROTTLE_BRAKE:
                printf("\nThrottle1:      %d\n",throttle1);
                printf(  "Throttle2:      %d\n",throttle2);
                printf(  "Brake:          %d\n\n",brake);
                break;
            case BATTERY_DEBUG_VOLTS:
                printf("\nBat1:  %dV Bat2:  %dV Bat3:  %dV Bat4:  %dV  \n", milliVolts[0],milliVolts[1],milliVolts[2],milliVolts[3]);
                printf(  "Bat5:  %dV Bat6:  %dV Bat7:  %dV Bat8:  %dV  \n", milliVolts[4],milliVolts[5],milliVolts[6],milliVolts[7]);
                printf(  "Bat9:  %dV Bat10: %dV Bat11: %dV Bat12: %dV  \n", milliVolts[8],milliVolts[9],milliVolts[10],milliVolts[11]);
                printf(  "Bat13: %dV Bat14: %dV Bat15: %dV Bat16: %dV  \n\n", milliVolts[12],milliVolts[13],milliVolts[14],milliVolts[15]);

                break;
            case BATTERY_DEBUG_TEMPS:
                printf("\nBat1:  %dF   Bat2:  %dF   Bat3:  %dF   Bat4:  %dF  \n", temps[0],temps[1],temps[2],temps[3]);
                printf(  "Bat5:  %dF   Bat6:  %dF   Bat7:  %dF   Bat8:  %dF  \n", temps[4],temps[5],temps[6],temps[7]);
                printf(  "Bat9:  %dF   Bat10: %dF   Bat11: %dF   Bat12: %dF  \n", temps[8],temps[9],temps[10],temps[11]);
                printf(  "Bat13: %dF   Bat14: %dF   Bat15: %dF   Bat16: %dF  \n\n", temps[12],temps[13],temps[14],temps[15]);
                break;
            case BATTERY_DEBUG_POWER:
                printf("\nCurrent Pack 1:  %d\n", current1);
                printf(  "Current Pack 2:  %d\n", current2);
                printf(  "HV pack voltage: %d\n", bigVolts);
                break;           
        }
        DebugTimer=0;
    }

    if (receiveData2()) {
        ToSend2(RESPONSE_ADDRESS, ECU_ADDRESS);
        sendData2(DEBUG_ADDRESS);
    }

}