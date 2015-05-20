#include "DigiPot.h"
#include "xc.h"
#include "PinDef.h"
#include "Function.h"


int prev_pos = 0;

void PotSetpoint(int new_point)
{
    int set_point;

    if(new_point > 32)
    {
        new_point = 32;
    }
    if(new_point <= 0)
    {
        new_point = 0;
    }

    int new_pos = new_point;//(new_point/100)*32;

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

    int x;
    for(x = 0;x < set_point;x++)
    {
        DIGI_INC = 1;
        Delay(1);
        DIGI_INC = 0;
        Delay(1);
    }
    //We are done, let it go
    DIGI_CS = 1;
    prev_pos = new_pos;

}

void PotClear(void)
{
    //!CS this Bitch
    DIGI_CS = 0;
    Delay(1);
    DIGI_UP_DN = 0;
    Delay(1);
    int x;
    for(x = 0;x < 32;x++)
    {
        DIGI_INC = 1;
        Delay(1);
        DIGI_INC = 0;
        Delay(1);
    }
    //We are done, let it go
    DIGI_CS = 1;
    prev_pos = 0;
}