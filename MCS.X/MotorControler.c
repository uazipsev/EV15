/*
 * File:   MotorController.c
 * Author: Rick
 *
 * Created on May 20, 2015, 3:05 AM
 *
 * This controls the IO for the motor controller
 * It uses the MCP4725 and IO to set modes of the device (ex FW / REV)
 *
 * Data sheet:
 */

#include "MotorControler.h"
#include <stdbool.h>
#include "PinDef.h"
#include "Function.h"
#include "MCP4725.h"
#include "UART_2.h"
#include <xc.h>


void SetMotorDefaults() {
    SetDAC1(0);
    SetDAC2(0);
}

void MotorEnable() {
    LATAbits.LATA0=1;
    //BRAKE =1;
    DC12ENABLE;
    FORWARD=1;
    REVERSE=0;
}

void MotorDisable() {
    //DC12DISABLE;
    //BRAKE =0;
}

//sets the direction of the motor and sets speed

void SetMotor(int speed, int direction) {
    //directionMismatchCheck(direction);
    SetDAC2(speed);
}

bool motorControllerValuesCheck(int t, int b) {
    //As long as the brake and gas are not both applied heavily
    if (b > 75 && t > 75) {
        return false;
    }
    return true;
}

void directionMismatchCheck(int direction) {
    static int past_direction = backward;
    if ((direction == forward) && (past_direction == backward)) {
        SetDAC2(0);
        //Delay(100);
        REVERSE = 0;
        //Delay(100);
        FORWARD = 1;
        past_direction = direction;
        
        //BRAKE =0;
    } else if ((direction == backward) && (past_direction == forward)) {
        SetDAC2(0);
        Delay(100);
        FORWARD = 0;
        Delay(100);
        //REVERSE = 1;
        past_direction = direction;
    }
}

//Set Regen amout ( to DAC)

void SetRegen(int amount) {
    static int lastRegen;
    if(amount != lastRegen){
    SetDAC1(amount);
    lastRegen=amount;
    }
}

// toggles regen

void Regen(bool enable) {
    if (enable == 1) {
        REGENEN = 1;
    } else
        REGENEN = 0;
}

// Turns on data and analize input
//needs work

void StartMCData(void) {
    //send "+CRLF" + is in askii
    char Start[] = "+\r\n";
    Send2_put(Start);
}

void GetMCData(void) {
    char data[60];
    int x = 0;
    while(Receive2_available()){
        data[x] = Receive2_get();
        x+=1;
    }
}