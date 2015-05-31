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

//sets the direction of the motor and sets speed
void SetMotor(int speed, dirr direction)
{
    if((direction == forward) && (past_dirrection == backward))
    {
        SetDAC1(0);
        Delay(2000);
        REVERSE = 0;
        Delay(6000);
        FORWARD = 1;
        Delay(2000);
        SetDAC1(speed);
    }
    if((direction == backward) && (past_dirrection == forward))
    {
        SetDAC1(0);
        Delay(2000);
        FORWARD = 0;
        Delay(6000);
        REVERSE = 1;
        Delay(2000);
        SetDAC1(speed);
    }
}


//Set Regen amout ( to DAC)
void SetRegen(int amount)
{
    SetDAC2(amount);
}

// toggles regen
void Regen(bool enable)
{
    if(enable == 1)
    {
        REGENEN  = 1;
    }
    else
        REGENEN  = 0;
}

// Turns on data and analize input
//needs work
void GetMCData(void)
{
    //send "+CRLF" + is in askii
    
}
