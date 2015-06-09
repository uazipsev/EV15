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
#include <xc.h>

int past_dirrection = 0;

void directionMismatchCheck(int direction);
//sets the direction of the motor and sets speed

void SetMotor(int speed, int direction) {
    directionMismatchCheck(direction);
    static int lastSetSpeed;
    if (speed != lastSetSpeed) {
        lastSetSpeed = speed;
        SetDAC1(speed);
    }

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
    if ((direction == forward) && (past_dirrection == backward)) {
        SetDAC1(0);
        Delay(100);
        REVERSE = 0;
        Delay(100);
        FORWARD = 1;
        Delay(100);
        past_direction = direction;
    } else if ((direction == backward) && (past_dirrection == forward)) {
        SetDAC1(0);
        Delay(2000);
        FORWARD = 0;
        Delay(6000);
        REVERSE = 1;
        Delay(2000);
        past_direction = direction;
    }
}
//Set Regen amout ( to DAC)

void SetRegen(int amount) {
    static int lastRegen;
    if(amount != lastRegen){
    SetDAC2(amount);
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

void GetMCData(void) {
    //send "+CRLF" + is in askii

}
