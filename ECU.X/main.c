/* 
 * File:   main.c
 * Author: Rick
 *
 * Created on May 11, 2015, 11:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "xc.h"
#include "PinDef.h"
#include "ADDRESSING.h"
#include "main.h"
#include "debug.h"

struct powerStates {
    bool DDS;
    bool MCS;
    bool SAS;
    bool BMM;
} powerSet;
struct commsStates {
    
    bool DDS;
    bool MCS;
    bool SAS;
    bool BMM;
    bool PDU;
}comms;
struct faultStates {
    int DDS;
    int MCS;
    int SAS;
    int BMM;
    int PDU;
    int SS;
} faults;

enum ECUstates {
    stopped = 0,
    booting = 1,
    running = 2,
    stopping = 3,
    fault      = 4,
    NUM_STATES = 5
} currentState;

int main(int argc, char** argv) {
    Setup();
    Delay(1000);
    while (1) {
        ledDebug();
        updateComms();
        updateECUState();
        updateBrakeLight();
    }
    return (EXIT_SUCCESS);
}

void updateBrakeLight() {
    if (brake > 10) {
        BRAKELT = 1;
    } else BRAKELT = 0;
}

bool faultChecker(){
    return false;
}

bool bootSequenceCompleted(){
    
    if(BootTimer>3000)   return true;
    else return false;
}
void updateECUState() {
    static enum ECUstates previousState = NUM_STATES;
    switch (currentState) {
        case stopped:
            //Means this is your first time in this state
            if (previousState != currentState) {
                changeLEDState(IMD_INDICATOR, 0);
                changeLEDState(BMS_LED, 0);
                previousState = currentState;
                powerSet.DDS = true;
                powerSet.SAS = true;
                powerSet.BMM = true;
                powerSet.MCS = false;
                SS_RELAY=0;
            }
            handleDebugRequests();
            //If start button is depressed, do start system request, show on LED
            if (seekButtonChange()) {
                if(!buttonArray[START_BUTTON]){
                    changeLEDState(ACTIVE_LED, !buttonArray[START_BUTTON]);
                    currentState++;
                }
            }
            break;
        case booting:
            //Means this is your first time in this state
            if (previousState != currentState) {
                previousState = currentState;
                powerSet.MCS = true;                             
                SS_RELAY = 1;    
                BootTimer=0;
            }
            if(bootSequenceCompleted() && comms.MCS &&){                
                currentState++;
            }
            else
            {
                if(BootTimer>0 && BootTimer<=5){                    
                    changeLEDState(ACTIVE_LED, 0);
                }
                else if(BootTimer>250 && BootTimer<=255){                    
                    changeLEDState(ACTIVE_LED, 1);
                }                
                else if(BootTimer>500 && BootTimer<=505){                    
                    changeLEDState(ACTIVE_LED, 0);                    
                }
                else if(BootTimer>750 && BootTimer<=755){                    
                    changeLEDState(ACTIVE_LED, 1);                    
                }                
                else if(BootTimer>1000 && BootTimer<=1005){                    
                    changeLEDState(ACTIVE_LED, 0);                    
                }
                else if(BootTimer>1250 && BootTimer<=1255){                    
                    changeLEDState(ACTIVE_LED, 1);                    
                }                
                else if(BootTimer>1500 && BootTimer<=1505){                    
                    changeLEDState(ACTIVE_LED, 0);                    
                }
                else if(BootTimer>1750 && BootTimer<=1755){                    
                    changeLEDState(ACTIVE_LED, 1);                    
                }                
                else if(BootTimer>2000 && BootTimer<=2005){                    
                    changeLEDState(ACTIVE_LED, 0);                    
                }
                else if(BootTimer>2250 && BootTimer<=2255){                    
                    changeLEDState(ACTIVE_LED, 1);                    
                }                
                else if(BootTimer>2500 && BootTimer<=2505){                    
                    changeLEDState(ACTIVE_LED, 0);                    
                }
                else if(BootTimer>2750 && BootTimer<=2755){                    
                    changeLEDState(ACTIVE_LED, 1);                    
                }
            }
            //if start button changes to depressed here, exit boot sequence
            if (seekButtonChange()) {
                if(!buttonArray[START_BUTTON]){
                    changeLEDState(ACTIVE_LED, buttonArray[START_BUTTON]);
                    currentState--;
                }
            }
            break;
        case running:
            //Means this is your first time in this state
            if (previousState != currentState) {
                previousState = currentState;
                
            }
            if(faultChecker()){
                currentState=fault;
                
            }
            
            if (seekButtonChange()) {
                if(!buttonArray[START_BUTTON]){
                    changeLEDState(ACTIVE_LED, buttonArray[START_BUTTON]);
                    currentState++;
                }
            }
            break;
        case stopping:
            //Means this is your first time in this state
            if (previousState != currentState) {
                previousState = currentState;
                changeLEDState(IMD_INDICATOR, 1);
                changeLEDState(BMS_LED, 1);
                BootTimer=0;
            }
            if(BootTimer>300){
                currentState=stopped;
            }
            
            break;
        case fault:
            //Means this is your first time in this state
            if (previousState != currentState) {
                previousState = currentState;
                
            }
            if (seekButtonChange()) {
                changeLEDState(IMD_INDICATOR, !buttonArray[AUX_BUTTON]);
                changeLEDState(ACTIVE_LED, !buttonArray[START_BUTTON]);
            }
            break;
        case NUM_STATES:
            //Means this is your first time in this state
            if (previousState != currentState) {
                previousState = currentState;
                
            }
            break;
    }

}