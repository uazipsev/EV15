#include "Communications.h"
#include "MotorControler.h"
int throttleOut = 0, brakeOut = 0;
bool pendingSend = false;
bool portClosed = true;

void commSafety();
void updateComms() {
    checkCommDirection();
    if (receiveData()) {
        static bool carActive = false;
        carActive=receiveArray[OUTPUT_ACTIVE];
        if (carActive) {
            //If 12 volts to motor controller is not on, turn it on
            if(!PORTAbits.RA10){
                LATAbits.LATA10=1;
            }
            //If DAC relay is not on, turn it on
             if(!PORTAbits.RA0){
                 LATAbits.LATA0=1;
             }
            //if the output is not what we received, set it correctly 
            if (throttleOut != receiveArray[THROTTLE_OUTPUT]) {
                throttleOut = receiveArray[THROTTLE_OUTPUT];
                SetMotor(throttleOut, 1);
            }
            //if the output is not what we received, set it correctly 
            if (brakeOut != receiveArray[BRAKE_OUTPUT]) {
                brakeOut = receiveArray[BRAKE_OUTPUT];
                SetRegen(brakeOut);
            }
        }
        //else we have received a request to not be active
        else{
            //if brake is non-zero, wipe it
            if(brakeOut!=0){
                brakeOut=0;
                SetRegen(0);
            }
            //if throttle is non-zero, wipe it
            if(throttleOut!=0){
                throttleOut=0;
                SetMotor(0,1);
            }
            //Relay control.
            LATAbits.LATA0=0;
            //12 volts to motor controller 
            LATAbits.LATA10=0;
        }
        talkTime = 0;
        safetyTime = 0;
        pendingSend = true;
    }
    //Control the RS485 Direction pin based on time and sending
    if (pendingSend && portClosed && talkTime > 5) {
        talkTime = 0;
        portClosed = false;
        RS485_1_Port = TALK;
    }
    //Respond to the ECU when the portHas been open for a short time
    if (pendingSend && talkTime > 1 && !portClosed) {
        talkTime = 0;
        respondECU();
        pendingSend = false;
    }
    //Provide safety timer
    commSafety();
}

//If the safety timer overruns 200 then shut off outputs and set DACs to 0
void commSafety() {
    if (safetyTime > 200) {
        SetMotor(0, 1);
        SetRegen(0);
        //Motor controller 12V
        LATAbits.LATA10=0;
        //Relay for DAC
        LATAbits.LATA0=0;
    }
}
//Shoot a packet to the ECU
void respondECU() {
    ToSend(RESPONSE_ADDRESS, MCS_ADDRESS);
    sendData(ECU_ADDRESS);
    talkTime = 0;
}

void checkCommDirection() {
    //you have finished send and time has elapsed.. start listen
    if (Transmit_stall && (talkTime > 5) && (RS485_1_Port == TALK)) {
        RS485_1_Port = LISTEN;
        portClosed = true;
    }
}
