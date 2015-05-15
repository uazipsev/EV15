#include "DigiPot.h"
#include "xc.h"
#include "PinDef.h"
#include "Function.h"


int prev_pos;

void PotSetValue(int value)
{

}

void PotSetpoint(int new_point)
{
    int set_point;

    if(new_point > 100)
    {
        new_point = 100;
    }
    if(new_point <= 0)
    {
        new_point = 0;
    }

    int new_pos = (new_point/100)*32;

    //!CS this Bitch
    DIGI_CS = 0;

    if(new_pos > prev_pos)
    {
        DIGI_UP_DN = 1;
        set_point = new_pos - prev_pos;
    }
    if(new_pos < prev_pos)
    {
        DIGI_UP_DN = 0;
        set_point = prev_pos - new_pos;
    }

    for(;;)
    {
        Delay(1);
    }
    //We are done, let it go
    DIGI_CS = 1;

}