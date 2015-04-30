#include <xc.h>
#include "Define.h"
#include "Bypass.h"
#include "Global.h"
#include "Battery.h"
#include "mcc_generated_files/pin_manager.h"

int SetBypas(int pin, int state)
{
    switch (pin) {
        case 0:
            if (state)
            {
                Bypass1_SetHigh();
            }
            else
            {
                Bypass1_SetLow();
            }
            break;
        case 1:
            if (state)
            {
                Bypass2_SetHigh();
            }
            else
            {
                Bypass2_SetLow();
            }
            break;
        case 2:
            if (state)
            {
                Bypass3_SetHigh();
            }
            else
            {
                Bypass3_SetLow();
            }
            break;
        case 3:
            if (state)
            {
                Bypass4_SetHigh();
            }
            else
            {
                Bypass4_SetLow();
            }
            break;
        case 4:
            if (state)
            {
                Bypass5_SetHigh();
            }
            else
            {
                Bypass5_SetLow();
            }
            break;
        case 5:
            if (state)
            {
                Bypass6_SetHigh();
            }
            else
            {
                Bypass6_SetLow();
            }
            break;
        case 6:
            if (state)
            {
                Bypass7_SetHigh();
            }
            else
            {
                Bypass7_SetLow();
            }
            break;
        case 7:
            if (state)
            {
                Bypass8_SetHigh();
            }
            else
            {
                Bypass8_SetLow();
            }
            break;
        case 8:
            if (state)
            {
                Bypass9_SetHigh();
            }
            else
            {
                Bypass9_SetLow();
            }
            break;
        case 9:
            if (state)
            {
                Bypass10_SetHigh();
            }
            else
            {
                Bypass10_SetLow();
            }
            break;
    }
}

int RunBypas()
{
    int cellbyp = 0;
    int i = 0;
    float batvolt = 0;

    for(i = 0; i<NUMOFBATT;i++)
    {
        batvolt = Battery_Get(i);

        if(batvolt >= BATBYPON)
        {
           SetBypas(i,1);
           cellbyp = 1;
        }
        if(batvolt <= BATBYPOFF)
        {
           SetBypas(i,0);
           cellbyp = 1;
        }
    }
    return cellbyp;
}
