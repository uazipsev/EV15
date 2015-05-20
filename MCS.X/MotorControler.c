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
        REVERSE = 0;
        FORWARD = 1;
        SetDAC1(speed);
    }
    if(direction == backward)
    {
        FORWARD = 0;
        REVERSE = 1;
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
