#include <xc.h>
#include "Define.h"
#include "Bypass.h"
#include "Global.h"
#include "Battery.h"
#include "mcc_generated_files/pin_manager.h"




/*******************************************************************
 * @brief           Controls Bypass
 * @param[in]       pin - what battery to control the bypass on
 * @param[in]       state - turn bypass on or off
 * @return          nothing
 * @note            Like to make this fcn better
 *******************************************************************/
int SetBypass(int pin, int state)
{
    switch (pin) {                   //<! sellects proper pin to control
        case 0:
            if (state)
            {
                Bypass1_SetHigh();   //<! sets high to turn on or low to turn off
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

/*******************************************************************
 * @brief           Controls Bypass
 * @return          did we need a bypass? returns 1 if yes 0 if no
 * @note            works well with diffrent size systems
 *******************************************************************/
int RunBypas()
{
    int cellbyp = 0;
    int i = 0;
    float batvolt = 0;

    for(i = 0; i<NUMOFBATT;i++)      //<! runs threw num of batteries
    {
        batvolt = Battery_Get(i);    //<! gets battery voltage

        if(batvolt >= BATBYPON)      //<! if bypass needs enabled..
        {
           SetBypass(i,1);           //<! sets bypass on
           cellbyp = 1;
        }
        if(batvolt <= BATBYPOFF)     //<! if bypass needs turned off...
        {
           SetBypass(i,0);           //<! sets bypass off
        }
    }
    return cellbyp;
}
