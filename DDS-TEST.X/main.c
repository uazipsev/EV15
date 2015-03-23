
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
*               -Set LED Bar Graph -
*               -Read RS485 BUS for data and reply with expectied data (set requested LED states and rely with button states)
*********************************************************************************************************

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */
void main(void)
{
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
    int ADCNT = 0;
    INDICATOR_SetHigh();
    while (1)
    {
        ADCNT = ADC_GetConversion(Volume);
        // Add your application code
        printf("ADC Volume = %d",ADCNT);
        for(int i = 0; 50 > i ; i++)
        {
          __delay_ms(10);
        }

    }
}
/**
 End of File
*/