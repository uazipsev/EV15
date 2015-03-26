/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB® Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.10.2
        Device            :  PIC18F45K22
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.33
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA0 aliases
#define IO_RA0_TRIS               TRISA0
#define IO_RA0_LAT                LATA0
#define IO_RA0_PORT               PORTAbits.RA0
#define IO_RA0_ANS                ANSA0
#define IO_RA0_SetHigh()    do { LATA0 = 1; } while(0)
#define IO_RA0_SetLow()   do { LATA0 = 0; } while(0)
#define IO_RA0_Toggle()   do { LATA0 = ~LATA0; } while(0)
#define IO_RA0_GetValue()         PORTAbits.RA0
#define IO_RA0_SetDigitalInput()    do { TRISA0 = 1; } while(0)
#define IO_RA0_SetDigitalOutput()   do { TRISA0 = 0; } while(0)

#define IO_RA0_SetAnalogMode()   do { ANSA0 = 1; } while(0)
#define IO_RA0_SetDigitalMode()   do { ANSA0 = 0; } while(0)
// get/set Battery1 aliases
#define Battery1_TRIS               TRISA1
#define Battery1_LAT                LATA1
#define Battery1_PORT               PORTAbits.RA1
#define Battery1_ANS                ANSA1
#define Battery1_SetHigh()    do { LATA1 = 1; } while(0)
#define Battery1_SetLow()   do { LATA1 = 0; } while(0)
#define Battery1_Toggle()   do { LATA1 = ~LATA1; } while(0)
#define Battery1_GetValue()         PORTAbits.RA1
#define Battery1_SetDigitalInput()    do { TRISA1 = 1; } while(0)
#define Battery1_SetDigitalOutput()   do { TRISA1 = 0; } while(0)

#define Battery1_SetAnalogMode()   do { ANSA1 = 1; } while(0)
#define Battery1_SetDigitalMode()   do { ANSA1 = 0; } while(0)
// get/set Battery2 aliases
#define Battery2_TRIS               TRISA3
#define Battery2_LAT                LATA3
#define Battery2_PORT               PORTAbits.RA3
#define Battery2_ANS                ANSA3
#define Battery2_SetHigh()    do { LATA3 = 1; } while(0)
#define Battery2_SetLow()   do { LATA3 = 0; } while(0)
#define Battery2_Toggle()   do { LATA3 = ~LATA3; } while(0)
#define Battery2_GetValue()         PORTAbits.RA3
#define Battery2_SetDigitalInput()    do { TRISA3 = 1; } while(0)
#define Battery2_SetDigitalOutput()   do { TRISA3 = 0; } while(0)

#define Battery2_SetAnalogMode()   do { ANSA3 = 1; } while(0)
#define Battery2_SetDigitalMode()   do { ANSA3 = 0; } while(0)
// get/set Battery3 aliases
#define Battery3_TRIS               TRISA5
#define Battery3_LAT                LATA5
#define Battery3_PORT               PORTAbits.RA5
#define Battery3_ANS                ANSA5
#define Battery3_SetHigh()    do { LATA5 = 1; } while(0)
#define Battery3_SetLow()   do { LATA5 = 0; } while(0)
#define Battery3_Toggle()   do { LATA5 = ~LATA5; } while(0)
#define Battery3_GetValue()         PORTAbits.RA5
#define Battery3_SetDigitalInput()    do { TRISA5 = 1; } while(0)
#define Battery3_SetDigitalOutput()   do { TRISA5 = 0; } while(0)

#define Battery3_SetAnalogMode()   do { ANSA5 = 1; } while(0)
#define Battery3_SetDigitalMode()   do { ANSA5 = 0; } while(0)
// get/set MUX_A aliases
#define MUX_A_TRIS               TRISA6
#define MUX_A_LAT                LATA6
#define MUX_A_PORT               PORTAbits.RA6
#define MUX_A_SetHigh()    do { LATA6 = 1; } while(0)
#define MUX_A_SetLow()   do { LATA6 = 0; } while(0)
#define MUX_A_Toggle()   do { LATA6 = ~LATA6; } while(0)
#define MUX_A_GetValue()         PORTAbits.RA6
#define MUX_A_SetDigitalInput()    do { TRISA6 = 1; } while(0)
#define MUX_A_SetDigitalOutput()   do { TRISA6 = 0; } while(0)

// get/set Bypass7 aliases
#define Bypass7_TRIS               TRISB0
#define Bypass7_LAT                LATB0
#define Bypass7_PORT               PORTBbits.RB0
#define Bypass7_WPU                WPUB0
#define Bypass7_ANS                ANSB0
#define Bypass7_SetHigh()    do { LATB0 = 1; } while(0)
#define Bypass7_SetLow()   do { LATB0 = 0; } while(0)
#define Bypass7_Toggle()   do { LATB0 = ~LATB0; } while(0)
#define Bypass7_GetValue()         PORTBbits.RB0
#define Bypass7_SetDigitalInput()    do { TRISB0 = 1; } while(0)
#define Bypass7_SetDigitalOutput()   do { TRISB0 = 0; } while(0)

#define Bypass7_SetPullup()    do { WPUB0 = 1; } while(0)
#define Bypass7_ResetPullup()   do { WPUB0 = 0; } while(0)
#define Bypass7_SetAnalogMode()   do { ANSB0 = 1; } while(0)
#define Bypass7_SetDigitalMode()   do { ANSB0 = 0; } while(0)
// get/set Bypass8 aliases
#define Bypass8_TRIS               TRISB1
#define Bypass8_LAT                LATB1
#define Bypass8_PORT               PORTBbits.RB1
#define Bypass8_WPU                WPUB1
#define Bypass8_ANS                ANSB1
#define Bypass8_SetHigh()    do { LATB1 = 1; } while(0)
#define Bypass8_SetLow()   do { LATB1 = 0; } while(0)
#define Bypass8_Toggle()   do { LATB1 = ~LATB1; } while(0)
#define Bypass8_GetValue()         PORTBbits.RB1
#define Bypass8_SetDigitalInput()    do { TRISB1 = 1; } while(0)
#define Bypass8_SetDigitalOutput()   do { TRISB1 = 0; } while(0)

#define Bypass8_SetPullup()    do { WPUB1 = 1; } while(0)
#define Bypass8_ResetPullup()   do { WPUB1 = 0; } while(0)
#define Bypass8_SetAnalogMode()   do { ANSB1 = 1; } while(0)
#define Bypass8_SetDigitalMode()   do { ANSB1 = 0; } while(0)
// get/set Battery8 aliases
#define Battery8_TRIS               TRISB2
#define Battery8_LAT                LATB2
#define Battery8_PORT               PORTBbits.RB2
#define Battery8_WPU                WPUB2
#define Battery8_ANS                ANSB2
#define Battery8_SetHigh()    do { LATB2 = 1; } while(0)
#define Battery8_SetLow()   do { LATB2 = 0; } while(0)
#define Battery8_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define Battery8_GetValue()         PORTBbits.RB2
#define Battery8_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define Battery8_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define Battery8_SetPullup()    do { WPUB2 = 1; } while(0)
#define Battery8_ResetPullup()   do { WPUB2 = 0; } while(0)
#define Battery8_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define Battery8_SetDigitalMode()   do { ANSB2 = 0; } while(0)
// get/set Bypass9 aliases
#define Bypass9_TRIS               TRISB3
#define Bypass9_LAT                LATB3
#define Bypass9_PORT               PORTBbits.RB3
#define Bypass9_WPU                WPUB3
#define Bypass9_ANS                ANSB3
#define Bypass9_SetHigh()    do { LATB3 = 1; } while(0)
#define Bypass9_SetLow()   do { LATB3 = 0; } while(0)
#define Bypass9_Toggle()   do { LATB3 = ~LATB3; } while(0)
#define Bypass9_GetValue()         PORTBbits.RB3
#define Bypass9_SetDigitalInput()    do { TRISB3 = 1; } while(0)
#define Bypass9_SetDigitalOutput()   do { TRISB3 = 0; } while(0)

#define Bypass9_SetPullup()    do { WPUB3 = 1; } while(0)
#define Bypass9_ResetPullup()   do { WPUB3 = 0; } while(0)
#define Bypass9_SetAnalogMode()   do { ANSB3 = 1; } while(0)
#define Bypass9_SetDigitalMode()   do { ANSB3 = 0; } while(0)
// get/set Battery9 aliases
#define Battery9_TRIS               TRISB4
#define Battery9_LAT                LATB4
#define Battery9_PORT               PORTBbits.RB4
#define Battery9_WPU                WPUB4
#define Battery9_ANS                ANSB4
#define Battery9_SetHigh()    do { LATB4 = 1; } while(0)
#define Battery9_SetLow()   do { LATB4 = 0; } while(0)
#define Battery9_Toggle()   do { LATB4 = ~LATB4; } while(0)
#define Battery9_GetValue()         PORTBbits.RB4
#define Battery9_SetDigitalInput()    do { TRISB4 = 1; } while(0)
#define Battery9_SetDigitalOutput()   do { TRISB4 = 0; } while(0)

#define Battery9_SetPullup()    do { WPUB4 = 1; } while(0)
#define Battery9_ResetPullup()   do { WPUB4 = 0; } while(0)
#define Battery9_SetAnalogMode()   do { ANSB4 = 1; } while(0)
#define Battery9_SetDigitalMode()   do { ANSB4 = 0; } while(0)
// get/set Battery10 aliases
#define Battery10_TRIS               TRISB5
#define Battery10_LAT                LATB5
#define Battery10_PORT               PORTBbits.RB5
#define Battery10_WPU                WPUB5
#define Battery10_ANS                ANSB5
#define Battery10_SetHigh()    do { LATB5 = 1; } while(0)
#define Battery10_SetLow()   do { LATB5 = 0; } while(0)
#define Battery10_Toggle()   do { LATB5 = ~LATB5; } while(0)
#define Battery10_GetValue()         PORTBbits.RB5
#define Battery10_SetDigitalInput()    do { TRISB5 = 1; } while(0)
#define Battery10_SetDigitalOutput()   do { TRISB5 = 0; } while(0)

#define Battery10_SetPullup()    do { WPUB5 = 1; } while(0)
#define Battery10_ResetPullup()   do { WPUB5 = 0; } while(0)
#define Battery10_SetAnalogMode()   do { ANSB5 = 1; } while(0)
#define Battery10_SetDigitalMode()   do { ANSB5 = 0; } while(0)
// get/set MUX_B aliases
#define MUX_B_TRIS               TRISC0
#define MUX_B_LAT                LATC0
#define MUX_B_PORT               PORTCbits.RC0
#define MUX_B_SetHigh()    do { LATC0 = 1; } while(0)
#define MUX_B_SetLow()   do { LATC0 = 0; } while(0)
#define MUX_B_Toggle()   do { LATC0 = ~LATC0; } while(0)
#define MUX_B_GetValue()         PORTCbits.RC0
#define MUX_B_SetDigitalInput()    do { TRISC0 = 1; } while(0)
#define MUX_B_SetDigitalOutput()   do { TRISC0 = 0; } while(0)

// get/set MUX_C aliases
#define MUX_C_TRIS               TRISC1
#define MUX_C_LAT                LATC1
#define MUX_C_PORT               PORTCbits.RC1
#define MUX_C_SetHigh()    do { LATC1 = 1; } while(0)
#define MUX_C_SetLow()   do { LATC1 = 0; } while(0)
#define MUX_C_Toggle()   do { LATC1 = ~LATC1; } while(0)
#define MUX_C_GetValue()         PORTCbits.RC1
#define MUX_C_SetDigitalInput()    do { TRISC1 = 1; } while(0)
#define MUX_C_SetDigitalOutput()   do { TRISC1 = 0; } while(0)

// get/set Temp1 aliases
#define Temp1_TRIS               TRISC2
#define Temp1_LAT                LATC2
#define Temp1_PORT               PORTCbits.RC2
#define Temp1_ANS                ANSC2
#define Temp1_SetHigh()    do { LATC2 = 1; } while(0)
#define Temp1_SetLow()   do { LATC2 = 0; } while(0)
#define Temp1_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define Temp1_GetValue()         PORTCbits.RC2
#define Temp1_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define Temp1_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

#define Temp1_SetAnalogMode()   do { ANSC2 = 1; } while(0)
#define Temp1_SetDigitalMode()   do { ANSC2 = 0; } while(0)
// get/set Temp_INH aliases
#define Temp_INH_TRIS               TRISC3
#define Temp_INH_LAT                LATC3
#define Temp_INH_PORT               PORTCbits.RC3
#define Temp_INH_ANS                ANSC3
#define Temp_INH_SetHigh()    do { LATC3 = 1; } while(0)
#define Temp_INH_SetLow()   do { LATC3 = 0; } while(0)
#define Temp_INH_Toggle()   do { LATC3 = ~LATC3; } while(0)
#define Temp_INH_GetValue()         PORTCbits.RC3
#define Temp_INH_SetDigitalInput()    do { TRISC3 = 1; } while(0)
#define Temp_INH_SetDigitalOutput()   do { TRISC3 = 0; } while(0)

#define Temp_INH_SetAnalogMode()   do { ANSC3 = 1; } while(0)
#define Temp_INH_SetDigitalMode()   do { ANSC3 = 0; } while(0)
// get/set Bypass2 aliases
#define Bypass2_TRIS               TRISC4
#define Bypass2_LAT                LATC4
#define Bypass2_PORT               PORTCbits.RC4
#define Bypass2_ANS                ANSC4
#define Bypass2_SetHigh()    do { LATC4 = 1; } while(0)
#define Bypass2_SetLow()   do { LATC4 = 0; } while(0)
#define Bypass2_Toggle()   do { LATC4 = ~LATC4; } while(0)
#define Bypass2_GetValue()         PORTCbits.RC4
#define Bypass2_SetDigitalInput()    do { TRISC4 = 1; } while(0)
#define Bypass2_SetDigitalOutput()   do { TRISC4 = 0; } while(0)

#define Bypass2_SetAnalogMode()   do { ANSC4 = 1; } while(0)
#define Bypass2_SetDigitalMode()   do { ANSC4 = 0; } while(0)
// get/set Bypass1 aliases
#define Bypass1_TRIS               TRISC5
#define Bypass1_LAT                LATC5
#define Bypass1_PORT               PORTCbits.RC5
#define Bypass1_ANS                ANSC5
#define Bypass1_SetHigh()    do { LATC5 = 1; } while(0)
#define Bypass1_SetLow()   do { LATC5 = 0; } while(0)
#define Bypass1_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define Bypass1_GetValue()         PORTCbits.RC5
#define Bypass1_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define Bypass1_SetDigitalOutput()   do { TRISC5 = 0; } while(0)

#define Bypass1_SetAnalogMode()   do { ANSC5 = 1; } while(0)
#define Bypass1_SetDigitalMode()   do { ANSC5 = 0; } while(0)
// get/set TX1 aliases
#define TX1_TRIS               TRISC6
#define TX1_LAT                LATC6
#define TX1_PORT               PORTCbits.RC6
#define TX1_ANS                ANSC6
#define TX1_SetHigh()    do { LATC6 = 1; } while(0)
#define TX1_SetLow()   do { LATC6 = 0; } while(0)
#define TX1_Toggle()   do { LATC6 = ~LATC6; } while(0)
#define TX1_GetValue()         PORTCbits.RC6
#define TX1_SetDigitalInput()    do { TRISC6 = 1; } while(0)
#define TX1_SetDigitalOutput()   do { TRISC6 = 0; } while(0)

#define TX1_SetAnalogMode()   do { ANSC6 = 1; } while(0)
#define TX1_SetDigitalMode()   do { ANSC6 = 0; } while(0)
// get/set RX1 aliases
#define RX1_TRIS               TRISC7
#define RX1_LAT                LATC7
#define RX1_PORT               PORTCbits.RC7
#define RX1_ANS                ANSC7
#define RX1_SetHigh()    do { LATC7 = 1; } while(0)
#define RX1_SetLow()   do { LATC7 = 0; } while(0)
#define RX1_Toggle()   do { LATC7 = ~LATC7; } while(0)
#define RX1_GetValue()         PORTCbits.RC7
#define RX1_SetDigitalInput()    do { TRISC7 = 1; } while(0)
#define RX1_SetDigitalOutput()   do { TRISC7 = 0; } while(0)

#define RX1_SetAnalogMode()   do { ANSC7 = 1; } while(0)
#define RX1_SetDigitalMode()   do { ANSC7 = 0; } while(0)
// get/set Temp2 aliases
#define Temp2_TRIS               TRISD0
#define Temp2_LAT                LATD0
#define Temp2_PORT               PORTDbits.RD0
#define Temp2_ANS                ANSD0
#define Temp2_SetHigh()    do { LATD0 = 1; } while(0)
#define Temp2_SetLow()   do { LATD0 = 0; } while(0)
#define Temp2_Toggle()   do { LATD0 = ~LATD0; } while(0)
#define Temp2_GetValue()         PORTDbits.RD0
#define Temp2_SetDigitalInput()    do { TRISD0 = 1; } while(0)
#define Temp2_SetDigitalOutput()   do { TRISD0 = 0; } while(0)

#define Temp2_SetAnalogMode()   do { ANSD0 = 1; } while(0)
#define Temp2_SetDigitalMode()   do { ANSD0 = 0; } while(0)
// get/set Bypass5 aliases
#define Bypass5_TRIS               TRISD1
#define Bypass5_LAT                LATD1
#define Bypass5_PORT               PORTDbits.RD1
#define Bypass5_ANS                ANSD1
#define Bypass5_SetHigh()    do { LATD1 = 1; } while(0)
#define Bypass5_SetLow()   do { LATD1 = 0; } while(0)
#define Bypass5_Toggle()   do { LATD1 = ~LATD1; } while(0)
#define Bypass5_GetValue()         PORTDbits.RD1
#define Bypass5_SetDigitalInput()    do { TRISD1 = 1; } while(0)
#define Bypass5_SetDigitalOutput()   do { TRISD1 = 0; } while(0)

#define Bypass5_SetAnalogMode()   do { ANSD1 = 1; } while(0)
#define Bypass5_SetDigitalMode()   do { ANSD1 = 0; } while(0)
// get/set Bypass4 aliases
#define Bypass4_TRIS               TRISD2
#define Bypass4_LAT                LATD2
#define Bypass4_PORT               PORTDbits.RD2
#define Bypass4_ANS                ANSD2
#define Bypass4_SetHigh()    do { LATD2 = 1; } while(0)
#define Bypass4_SetLow()   do { LATD2 = 0; } while(0)
#define Bypass4_Toggle()   do { LATD2 = ~LATD2; } while(0)
#define Bypass4_GetValue()         PORTDbits.RD2
#define Bypass4_SetDigitalInput()    do { TRISD2 = 1; } while(0)
#define Bypass4_SetDigitalOutput()   do { TRISD2 = 0; } while(0)

#define Bypass4_SetAnalogMode()   do { ANSD2 = 1; } while(0)
#define Bypass4_SetDigitalMode()   do { ANSD2 = 0; } while(0)
// get/set Bypass3 aliases
#define Bypass3_TRIS               TRISD3
#define Bypass3_LAT                LATD3
#define Bypass3_PORT               PORTDbits.RD3
#define Bypass3_ANS                ANSD3
#define Bypass3_SetHigh()    do { LATD3 = 1; } while(0)
#define Bypass3_SetLow()   do { LATD3 = 0; } while(0)
#define Bypass3_Toggle()   do { LATD3 = ~LATD3; } while(0)
#define Bypass3_GetValue()         PORTDbits.RD3
#define Bypass3_SetDigitalInput()    do { TRISD3 = 1; } while(0)
#define Bypass3_SetDigitalOutput()   do { TRISD3 = 0; } while(0)

#define Bypass3_SetAnalogMode()   do { ANSD3 = 1; } while(0)
#define Bypass3_SetDigitalMode()   do { ANSD3 = 0; } while(0)
// get/set Battery5 aliases
#define Battery5_TRIS               TRISD4
#define Battery5_LAT                LATD4
#define Battery5_PORT               PORTDbits.RD4
#define Battery5_ANS                ANSD4
#define Battery5_SetHigh()    do { LATD4 = 1; } while(0)
#define Battery5_SetLow()   do { LATD4 = 0; } while(0)
#define Battery5_Toggle()   do { LATD4 = ~LATD4; } while(0)
#define Battery5_GetValue()         PORTDbits.RD4
#define Battery5_SetDigitalInput()    do { TRISD4 = 1; } while(0)
#define Battery5_SetDigitalOutput()   do { TRISD4 = 0; } while(0)

#define Battery5_SetAnalogMode()   do { ANSD4 = 1; } while(0)
#define Battery5_SetDigitalMode()   do { ANSD4 = 0; } while(0)
// get/set Bypass6 aliases
#define Bypass6_TRIS               TRISD5
#define Bypass6_LAT                LATD5
#define Bypass6_PORT               PORTDbits.RD5
#define Bypass6_ANS                ANSD5
#define Bypass6_SetHigh()    do { LATD5 = 1; } while(0)
#define Bypass6_SetLow()   do { LATD5 = 0; } while(0)
#define Bypass6_Toggle()   do { LATD5 = ~LATD5; } while(0)
#define Bypass6_GetValue()         PORTDbits.RD5
#define Bypass6_SetDigitalInput()    do { TRISD5 = 1; } while(0)
#define Bypass6_SetDigitalOutput()   do { TRISD5 = 0; } while(0)

#define Bypass6_SetAnalogMode()   do { ANSD5 = 1; } while(0)
#define Bypass6_SetDigitalMode()   do { ANSD5 = 0; } while(0)
// get/set Battery6 aliases
#define Battery6_TRIS               TRISD6
#define Battery6_LAT                LATD6
#define Battery6_PORT               PORTDbits.RD6
#define Battery6_ANS                ANSD6
#define Battery6_SetHigh()    do { LATD6 = 1; } while(0)
#define Battery6_SetLow()   do { LATD6 = 0; } while(0)
#define Battery6_Toggle()   do { LATD6 = ~LATD6; } while(0)
#define Battery6_GetValue()         PORTDbits.RD6
#define Battery6_SetDigitalInput()    do { TRISD6 = 1; } while(0)
#define Battery6_SetDigitalOutput()   do { TRISD6 = 0; } while(0)

#define Battery6_SetAnalogMode()   do { ANSD6 = 1; } while(0)
#define Battery6_SetDigitalMode()   do { ANSD6 = 0; } while(0)
// get/set Battery7 aliases
#define Battery7_TRIS               TRISD7
#define Battery7_LAT                LATD7
#define Battery7_PORT               PORTDbits.RD7
#define Battery7_ANS                ANSD7
#define Battery7_SetHigh()    do { LATD7 = 1; } while(0)
#define Battery7_SetLow()   do { LATD7 = 0; } while(0)
#define Battery7_Toggle()   do { LATD7 = ~LATD7; } while(0)
#define Battery7_GetValue()         PORTDbits.RD7
#define Battery7_SetDigitalInput()    do { TRISD7 = 1; } while(0)
#define Battery7_SetDigitalOutput()   do { TRISD7 = 0; } while(0)

#define Battery7_SetAnalogMode()   do { ANSD7 = 1; } while(0)
#define Battery7_SetDigitalMode()   do { ANSD7 = 0; } while(0)
// get/set Battery4 aliases
#define Battery4_TRIS               TRISE0
#define Battery4_LAT                LATE0
#define Battery4_PORT               PORTEbits.RE0
#define Battery4_ANS                ANSE0
#define Battery4_SetHigh()    do { LATE0 = 1; } while(0)
#define Battery4_SetLow()   do { LATE0 = 0; } while(0)
#define Battery4_Toggle()   do { LATE0 = ~LATE0; } while(0)
#define Battery4_GetValue()         PORTEbits.RE0
#define Battery4_SetDigitalInput()    do { TRISE0 = 1; } while(0)
#define Battery4_SetDigitalOutput()   do { TRISE0 = 0; } while(0)

#define Battery4_SetAnalogMode()   do { ANSE0 = 1; } while(0)
#define Battery4_SetDigitalMode()   do { ANSE0 = 0; } while(0)
// get/set MODE_REDE aliases
#define MODE_REDE_TRIS               TRISE1
#define MODE_REDE_LAT                LATE1
#define MODE_REDE_PORT               PORTEbits.RE1
#define MODE_REDE_ANS                ANSE1
#define MODE_REDE_SetHigh()    do { LATE1 = 1; } while(0)
#define MODE_REDE_SetLow()   do { LATE1 = 0; } while(0)
#define MODE_REDE_Toggle()   do { LATE1 = ~LATE1; } while(0)
#define MODE_REDE_GetValue()         PORTEbits.RE1
#define MODE_REDE_SetDigitalInput()    do { TRISE1 = 1; } while(0)
#define MODE_REDE_SetDigitalOutput()   do { TRISE1 = 0; } while(0)

#define MODE_REDE_SetAnalogMode()   do { ANSE1 = 1; } while(0)
#define MODE_REDE_SetDigitalMode()   do { ANSE1 = 0; } while(0)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);

#endif // PIN_MANAGER_H
/**
 End of File
*/