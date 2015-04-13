/**
  TMR2 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr2.h

  @Summary
    This is the generated header file for the TMR2 driver using MPLAB� Code Configurator

  @Description
    This header file provides APIs for TMR2.
    Generation Information :
        Product Revision  :  MPLAB� Code Configurator - v2.10.3
        Device            :  PIC18F45K22
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X 2.26
*/

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*/

#ifndef _TMR2_H
#define _TMR2_H

/**
  Section: Included Files
*/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif


/**
  Section: Macro Declarations
*/

/**
  Section: TMR2 APIs
*/

/**
  @Summary
    Initializes the TMR2 module.

  @Description
    This function initializes the TMR2 Registers.
    This function must be called before any other TMR2 function is called.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    

  @Example
    <code>
    main()
    {
        // Initialize TMR2 module
        TMR2_Initialize();

        // Do something else...
    }
    </code>
*/
void TMR2_Initialize(void);

/**
  @Summary
    This function starts the TMR2.

  @Description
    This function starts the TMR2 operation.
    This function must be called after the initialization of TMR2.

  @Preconditions
    Initialize  the TMR2 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize TMR2 module

    // Start TMR2
    TMR2_StartTimer();

    // Do something else...
    </code>
*/
void TMR2_StartTimer(void);

/**
  @Summary
    This function stops the TMR2.

  @Description
    This function stops the TMR2 operation.
    This function must be called after the start of TMR2.

  @Preconditions
    Initialize  the TMR2 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize TMR2 module

    // Start TMR2
    TMR2_StartTimer();

    // Do something else...

    // Stop TMR2;
    TMR2_StopTimer();
    </code>
*/
void TMR2_StopTimer(void);

/**
  @Summary
    Reads the TMR2 register.

  @Description
    This function reads the TMR2 register value and return it.

  @Preconditions
    Initialize  the TMR2 before calling this function.

  @Param
    None

  @Returns
    This function returns the current value of TMR2 register.

  @Example
    <code>
    // Initialize TMR2 module

    // Start TMR2
    TMR2_StartTimer();

    // Read the current value of TMR2
    if(0 == TMR2_ReadTimer())
    {
        // Do something else...

        // Reload the TMR value
        TMR2_Reload();
    }
    </code>
*/
uint8_t TMR2_ReadTimer(void);

/**
  @Summary
    Writes the TMR2 register.

  @Description
    This function writes the TMR2 register.
    This function must be called after the initialization of TMR2.

  @Preconditions
    Initialize  the TMR2 before calling this function.

  @Param
    timerVal - Value to write into TMR2 register.

  @Returns
    None

  @Example
    <code>
    #define PERIOD 0x80
    #define ZERO   0x00

    while(1)
    {
        // Read the TMR2 register
        if(ZERO == TMR2_ReadTimer())
        {
            // Do something else...

            // Write the TMR2 register
            TMR2_WriteTimer(PERIOD);
        }

        // Do something else...
    }
    </code>
*/
void TMR2_WriteTimer(uint8_t timerVal);

/**
  @Summary
    Load value to Period Register.

  @Description
    This function writes the value to PR2 register.
    This function must be called after the initialization of TMR2.

  @Preconditions
    Initialize  the TMR2 before calling this function.

  @Param
    periodVal - Value to load into TMR2 register.

  @Returns
    None

  @Example
    <code>
    #define PERIOD1 0x80
    #define PERIOD2 0x40
    #define ZERO    0x00

    while(1)
    {
        // Read the TMR2 register
        if(ZERO == TMR2_ReadTimer())
        {
            // Do something else...

            if(flag)
            {
                flag = 0;

                // Load Period 1 value
                TMR2_LoadPeriodRegister(PERIOD1);
            }
            else
            {
                 flag = 1;

                // Load Period 2 value
                TMR2_LoadPeriodRegister(PERIOD2);
            }
        }

        // Do something else...
    }
    </code>
*/
void TMR2_LoadPeriodRegister(uint8_t periodVal);

/**
  @Summary
    Timer Interrupt Service Routine

  @Description
    Timer Interrupt Service Routine is called by the Interrupt Manager.

  @Preconditions
    Initialize  the TMR2 module with interrupt before calling this isr.

  @Param
    None

  @Returns
    None
*/
void TMR2_ISR(void);

/**
  @Summary
    CallBack function

  @Description
    This function is called from the timer ISR. User can write your code in this function.

  @Preconditions
    Initialize  the TMR2 module with interrupt before calling this function.

  @Param
    None

  @Returns
    None
*/
 void TMR2_CallBack(void);

 #ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif // _TMR2_H
/**
 End of File
*/

