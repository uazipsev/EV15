/* 
 * File:   DDSBoardMain.c
 * Author: Rick
 *
 * Created on March 6, 2015, 1:51 AM
 */
#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <stdlib.h>

bool butnarray[8];

void SetLEDOut(int lednum, bool state) {
    switch (lednum) {
        case 0:
            if (state)LED0_SetHigh();
            else LED0_SetLow();
            break;
        case 1:
            if (state)LED1_SetHigh();
            else LED1_SetLow();
            break;
        case 2:
            if (state)LED2_SetHigh();
            else LED2_SetLow();
            break;
        case 3:
            if (state)LED3_SetHigh();
            else LED3_SetLow();
            break;
        case 4:
            if (state)LED4_SetHigh();
            else LED4_SetLow();
            break;
        case 5:
            if (state)LED4_SetHigh();
            else LED4_SetLow();
            break;
    }
}

void ReadButtonState(int btnnum) {
    switch (btnnum) {
        case 0:
            butnarray[btnnum] = Button1_GetValue();
            break;
        case 1:
            butnarray[btnnum] = Button2_GetValue();
            break;
        case 2:
            butnarray[btnnum] = Button3_GetValue();
            break;
        case 3:
            butnarray[btnnum] = Button4_GetValue();
            break;
        case 4:
            butnarray[btnnum] = Button5_GetValue();
            break;
        case 5:
            butnarray[btnnum] = Button6_GetValue();
            break;
        case 6:
            butnarray[btnnum] = Button7_GetValue();
            break;
        case 7:
            butnarray[btnnum] = Button8_GetValue();
            break;

    }
}

bool GetButtonState(int btnnum) {
    return butnarray[btnnum - 1];
}