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
                BP_ENBL1_SetHigh();
            }
            else
            {
                BP_ENBL1_SetLow();
            }
            break;
        case 1:
            if (state)
            {
                BP_ENBL2_SetHigh();
            }
            else
            {
                BP_ENBL2_SetLow();
            }
            break;
        case 2:
            if (state)
            {
                BP_ENBL3_SetHigh();
            }
            else
            {
                BP_ENBL3_SetLow();
            }
            break;
        case 3:
            if (state)
            {
                BP_ENBL4_SetHigh();
            }
            else
            {
                BP_ENBL4_SetLow();
            }
            break;
        case 4:
            if (state)
            {
                BP_ENBL5_SetHigh();
            }
            else
            {
                BP_ENBL5_SetLow();
            }
            break;
        case 5:
            if (state)
            {
                BP_ENBL6_SetHigh();
            }
            else
            {
                BP_ENBL6_SetLow();
            }
            break;
        case 6:
            if (state)
            {
                BP_ENBL7_SetHigh();
            }
            else
            {
                BP_ENBL7_SetLow();
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
        else if(batvolt <= BATBYPOFF)
        {
           SetBypas(i,0);
           cellbyp = 0;
        }
    }
    return cellbyp;
}
