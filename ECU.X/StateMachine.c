#include <stdbool.h>
#include <stdlib.h>
#include <xc.h>
#include "PinDef.h"
#include "StateMachine.h"
#include "debug.h"
extern int buttonArray[8];
extern bool seekButtonChange();
extern void changeLEDState(int LED, bool state);
extern volatile unsigned int BootTimer;

extern enum debugStates debugState;

int DDS_FAULT_CONDITION, MCS_FAULT_CONDITION, SAS_FAULT_CONDITION, BMM_FAULT_CONDITION, PDU_FAULT_CONDITION, ECU_FAULT_CONDITION;

struct faultStates faults;
enum ECUstates currentState;
struct commsStates comms;
struct powerStates powerSet;

bool bootSequenceCompleted();
bool faultChecker();

void updateECUState() {
    static enum ECUstates previousState = NUM_STATES;
    switch (currentState) {
            //CAR IS NOT RUNNING AND CAN BE STARTED OR DEBUG
        case stopped:
            //Means this is your first time in this state
            if (previousState != currentState) {
                changeLEDState(IMD_INDICATOR, 0);
                changeLEDState(BMS_LED, 0);
                changeLEDState(ACTIVE_LED, 0);
                previousState = currentState;
                powerSet.DDS = true;
                powerSet.SAS = true;
                powerSet.BMM = true;
                powerSet.MCS = false;
                SS_RELAY = 0;
            }
            handleDebugRequests();
            //If start button is depressed, do start system request, show on LED
            if (seekButtonChange()) {
                if (!buttonArray[START_BUTTON]) {
                    changeLEDState(ACTIVE_LED, !buttonArray[START_BUTTON]);
                    currentState++;
                }
                if (!buttonArray[DEBUG_BUTTON]) {
                    if (debugState < NUM_DEBUG_STATES - 1) {
                        debugState++;
                    } else debugState = 0;
                    switch (debugState) {
                        case NO_DEBUG:
                            comms.BMM_SEND = BATTERY_FAULT;
                            break;
                        case THROTTLE_BRAKE:
                            break;
                        case BATTERY_DEBUG_VOLTS:
                            comms.BMM_SEND = BATTERY_VOLTS;
                            break;
                        case BATTERY_DEBUG_TEMPS:
                            comms.BMM_SEND = BATTERY_TEMPS;
                            break;
                        case BATTERY_DEBUG_POWER:
                            comms.BMM_SEND = BATTERY_POWER;
                            break;
                        case FAULT_RECOVERY:
                            break;
                        case NUM_DEBUG_STATES:
                            break;
                    }
                }
            }
            break;
            //CAR IS ATTEMPTING TO BOOT UP
        case booting:
            //Means this is your first time in this state
            if (previousState != currentState) {
                previousState = currentState;
                powerSet.MCS = true;
                SS_RELAY = 1;
                BootTimer = 0;
            }
            if (bootSequenceCompleted() && comms.MCS) {
                currentState++;
            } else {
                if (BootTimer > 0 && BootTimer <= 5) {
                    changeLEDState(ACTIVE_LED, 0);
                } else if (BootTimer > 250 && BootTimer <= 255) {
                    changeLEDState(ACTIVE_LED, 1);
                } else if (BootTimer > 500 && BootTimer <= 505) {
                    changeLEDState(ACTIVE_LED, 0);
                } else if (BootTimer > 750 && BootTimer <= 755) {
                    changeLEDState(ACTIVE_LED, 1);
                } else if (BootTimer > 1000 && BootTimer <= 1005) {
                    changeLEDState(ACTIVE_LED, 0);
                } else if (BootTimer > 1250 && BootTimer <= 1255) {
                    changeLEDState(ACTIVE_LED, 1);
                } else if (BootTimer > 1500 && BootTimer <= 1505) {
                    changeLEDState(ACTIVE_LED, 0);
                } else if (BootTimer > 1750 && BootTimer <= 1755) {
                    changeLEDState(ACTIVE_LED, 1);
                } else if (BootTimer > 2000 && BootTimer <= 2005) {
                    changeLEDState(ACTIVE_LED, 0);
                } else if (BootTimer > 2250 && BootTimer <= 2255) {
                    changeLEDState(ACTIVE_LED, 1);
                } else if (BootTimer > 2500 && BootTimer <= 2505) {
                    changeLEDState(ACTIVE_LED, 0);
                } else if (BootTimer > 2750 && BootTimer <= 2755) {
                    changeLEDState(ACTIVE_LED, 1);
                }
                if(BootTimer>3500) currentState--;
            }
            //if start button changes to depressed here, exit boot sequence
            if (seekButtonChange()) {
                if (!buttonArray[START_BUTTON]) {
                    changeLEDState(ACTIVE_LED, buttonArray[START_BUTTON]);
                    currentState--;
                }
            }
            break;
            //CAR IS RUNNING BREAK ON FAULTS OR ON BUTTON
        case running:
            //Means this is your first time in this state
            if (previousState != currentState) {
                previousState = currentState;
            }

            if (faultChecker()) {
                currentState = fault;
            }

            if (seekButtonChange()) {
                if (!buttonArray[START_BUTTON]) {
                    changeLEDState(ACTIVE_LED, buttonArray[START_BUTTON]);
                    currentState++;
                }
            }
            break;
            //MAY BE UNNECCESSARY BUT THIS STATE ALLOWS CAR TO SHUT DOWN SOFTLY
        case stopping:
            //Means this is your first time in this state
            if (previousState != currentState) {
                previousState = currentState;
                changeLEDState(IMD_INDICATOR, 1);
                changeLEDState(BMS_LED, 1);
                BootTimer = 0;
            }
            if (BootTimer > 300) {
                currentState = stopped;
            }

            break;
            //HANDLE THE FAULTS THAT BROUGHT YOU HERE
        case fault:
            //Means this is your first time in this state
            if (previousState != currentState) {
                previousState = currentState;

            }
            debugState=FAULT_RECOVERY;
            if (seekButtonChange()) {
                changeLEDState(IMD_INDICATOR, !buttonArray[DEBUG_BUTTON]);
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

bool faultChecker() {
    if (MCS_FAULT_CONDITION || DDS_FAULT_CONDITION || PDU_FAULT_CONDITION || SAS_FAULT_CONDITION || BMM_FAULT_CONDITION)
        return true;
    else
        return false;
}

bool bootSequenceCompleted() {

    if (BootTimer > 3000) return true;
    else return false;
}
