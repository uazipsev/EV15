#include "MotorControler.h"
#include <stdbool.h>
#include "PinDef.h"
#include "Function.h"
#include "MCP4725.h"
#include <xc.h>



void SetMotor(int speed, enum Directionality direction)
{
    if(direction == forward)
    {
        SetDAC1(0);
        Delay(2000);
        REVERSE = 0;
        Delay(6000);
        FORWARD = 1;
        Delay(2000);
        SetDAC1(speed);
    }
    if(direction == backward)
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

void SetRegen(int amount)
{
    SetDAC2(amount);
}

void Regen(bool enable)
{
    if(enable == 1)
    {
        REGENEN  = 1;
    }
    else
        REGENEN  = 0;
}

void GetMCData(void)
{
    //send "+CRLF" + is in askii
    
}
