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
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "Battery.h"
#include "Functions.h"
#include "Global.h"
#include "Bypass.h"
#include "Tempeture.h"
extern void updateComms();
int main(int argc, char** argv) {
    // Initialize the device
    SYSTEM_Initialize();

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
    //printf("Hi Rick");
    while (1)
    {
        if (Temp_Done)  //<! This alerts the user that we are done gathering data (Temp)
        {
            Temp_Convert();  //<! Gets ADC counts and converts it to temp (F)
            Temp_Fault();    //<! Detects over temp conditions
//            for (int x = 0;x<9;x++)
//            {
//                //printf("Temp %d = %f \r\n", x,Tempeture_Get(x));
//            }
        }
        if (Volt_Done)
        {
            Battery_Convert();     //<! Converts ADC counts to bat volts
            Battery_Fault();       //<! Detects over volt conditions
            RunBypas();            //<! Runs bypass on required batteries
//            for (int x = 0;x<9;x++)
//            {
//                //printf("Battery %d = %0.02f \r\n", x,Battery_Get(x));
//            }
        }
        updateComms();
//        
//        
//        for(int i = 0;i<10;i++)  //<! Checks bypass fcn's (turn them on)
//        {
//            SetBypass(i,1);
//            Delay(250);
//        }
//        Delay(1000);
//        for(int i = 0;i<10;i++)  //<! Checks bypass fcn's (turn them off)
//        {
//            SetBypass(i,0);
//            Delay(250);
//        }
//        
        //Delay(1000);
        //("Battery 2 = %d \r\n",ADC_GetConversion(Battery2));
        //printf("Battery 8 = %d \r\n",ADC_GetConversion(Battery8));
    }
    return (EXIT_SUCCESS);
}


