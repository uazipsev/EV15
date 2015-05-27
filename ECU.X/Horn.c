#include "horn.h"
#include "Function.h"
#include "pwm.h"
#include "PinDef.h"
#include <xc.h>

void RTD(int lenth)
{
    //Start horn
    HORN_EN = 1;   // Starting Horn
    PWMupdate(50);
    int x = 0;
    for(;x<lenth;x++)
    {
        PERupdate(80);
        Delay(25);
        PERupdate(40);
        Delay(25);
    }
    Delay(lenth);
    //end horn
}