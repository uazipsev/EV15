/**
*********************************************************************************************************
*
* @brief        DDS - This device reads in button presses and sets LEDS / bar graph
* @file         main.c
* @author       Richard Johnson - Mark K
* @moduleID
* @ingroup
*
*********************************************************************************************************
* @note  The Firmware shall:
*               -Read in button inputs (O1-O8)
*               -Set LED status (LED1-LED6)
*               -Set LED Bar Graph - http://www.adafruit.com/products/1721
*               -Read RS485 BUS for data and reply with expectied data (set requested LED states and rely with button states)
*********************************************************************************************************
 */

#include "mcc_generated_files/mcc.h"

#include <stdio.h>
#include <stdlib.h>



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
    while (1)
    {

    }
    return (EXIT_SUCCESS);
}


