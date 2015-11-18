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

// 1. Added Enums as state values. State 0 is the default value so if the function gets a number that is not known it will give it a zero. 
//          This can help for debug purposes and have a catch for any junk that goes into the function.
// 2. The other states are defined as a Enum to represent what each state meaning is.
 enum States { State_0_Default,State_1_LED_0_HIGH, State_2_LED_0_LOW, State_3_LED_1_HIGH,State_4_LED_1_LOW, State_5_LED_2_HIGH, State_6_LED_2_LOW, 
               State_7_LED_3_HIGH, State_8_LED_3_LOW, State_9_LED_4_HIGH,State_10_LED_4_LOW, State_11_LED_5_HIGH, State_12_LED_6_LOW
 };

// 1. This function gets the Lednum and the state of that led (on=1 or off=0) and then determines what state that the LED/function needs to be in. 
//      Then the  function will return the state value.
int SetLEDOut(int lednum, bool state) {
    int Current_State=0;
    
    switch (lednum) {
        case 0:
            if (state) Current_State=State_1_LED_0_HIGH;
            else Current_State=State_2_LED_0_LOW;
            break;
        case 1:
            if (state) Current_State=State_3_LED_1_HIGH;
            else Current_State=State_4_LED_1_LOW;
            break;
        case 2:
            if (state) Current_State=State_5_LED_2_HIGH;
            else Current_State=State_6_LED_2_LOW;
            break;
        case 3:
            if (state) Current_State=State_7_LED_3_HIGH;
            else Current_State=State_8_LED_3_LOW;
            break;
        case 4:
            if (state) Current_State=State_9_LED_4_HIGH;
            else Current_State=State_10_LED_4_LOW;
            break;
        case 5:
            if (state) Current_State=State_11_LED_5_HIGH;
            else Current_State=State_12_LED_6_LOW;
            break;
        default :
                Current_State=  State_0_Default;
                break;
    }
    
    return Current_State;
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