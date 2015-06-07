/**
*********************************************************************************************************
*
* @brief        BMS - This device reads in voltages and temps. It controls bypass and sends data over RS485
* @file         main.c
* @author       Richard Johnson
* @moduleID
* @ingroup
*
*********************************************************************************************************
* @note  The Firmware shall:
*               -Read in battery voltags (B1-B10)
*               -Read in Temp voltags (T1-T2)
*               -Set LED indicator
*               -Set Bypass (C1-C10)
*               -Read RS485 BUS for data and reply with expectied data
*********************************************************************************************************
 */

#include "mcc_generated_files/mcc.h"

#include <stdio.h>
#include <stdlib.h>
#include "Battery.h"
#include "Functions.h"
#include "Global.h"
#include "Tempeture.h"
#include "Functions.h"
#include "Bypass.h"
#include "Current.h"

char fault = 0;
char infault = 0;

int main(int argc, char** argv) {
    // Initialize the device
    SYSTEM_Initialize();

    Relay_SET_SetHigh();
    Delay(120);
    Relay_SET_SetLow();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowEnable();

    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();

    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    //int ADCNT = 0;
    //INDICATOR_SetHigh();
    LATCbits.LATC5 =1;
    printf("start");
    while (1)
    {
        
    printf("start");
        
        if (Temp_Done)
        {
            Temp_Done = 0;
            Temp_Convert();
            Temp_Fault();
            /*
            for (int x = 0;x<7;x++)
            {
                printf("Battery  temp %d = %0.02f \r\n", x+1,Tempeture_Get(x));
            }
            */
        }
        if (Volt_Done)
        {
            Volt_Done = 0;
            Battery_Convert();
            Battery_Fault();
            
            for (int x = 0;x<7;x++)
            {
                printf("Battery %d = %0.02f \r\n", x+1,Battery_Get(x));
            }
            
            RunBypas();
        }
        if (Current_Done)
        {
            Current_Done = 0;
            Current_Convert();
            fault = Current_Fault();
            printf("Current %d = %0.02f \r\n",Current_Get());
        }
        if((fault == 1) && (infault == 0))
        {
            //Shut down box
            infault = 1;
            Relay_RSET_SetHigh();
            Delay(40);
            Relay_RSET_SetLow();
            Delay(40);    
            printf("FAULT \r\n");
        }
        if((fault == 0) && (infault == 1))
        {
            //Restart box
            Relay_SET_SetHigh();
            Delay(40);
            Relay_SET_SetLow();
            Delay(40);
        }
/*
        for(int y = 0;y<7;y++)
        {
            SetBypas(y,1);
            Delay(500);
            //BP_ENBL1_SetHigh();
        }
        
        for(int y = 0;y<7;y++)
        {
            SetBypas(y,0);
            Delay(500);
            //BP_ENBL1_SetLow();
        }
*/
        /*
        if (Volt_Done)
        {
            Battery_Convert();
            Battery_Fault();
        }
        */
        //printf("shit");
    }
    return (EXIT_SUCCESS);
}


