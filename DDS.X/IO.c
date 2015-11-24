
/* 
 * File:   DDSBoardMain.c
 * Author: Andrew T
 *
 * Created on March 6, 2015, 1:51 AM
 */
#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <stdlib.h>
// Arrays to recorded the button and LED state.
int LED_array[8];
bool butnarray[8];


/* Sets a certain LED to the appropriate state given as a argument and then records the state of that LED that it is in.
 Arguments:  
   lednum= the led you specified that will change its state.
   State= the state of that LED is in. State=1(LED On),2 (LED Off),3 (LED is blinking)
 
 After this function changes the LED's state in then records that state it just changed to. */
  
void SetLEDOut(int lednum, bool state) {
    switch (lednum) {
        case 0:
            if (state == 1) {
                LED0_SetHigh();
                LED_array[0] = 1;
            }
            else if (state == 0) {
                LED0_SetLow();
                LED_array[0] = 0;
            }

            else if (state == 2) {
                /*Setup timer here for interupts or enable interupt flag for timer.
                 Thinking that the function will be like 
                 Blinkstart(lednum) which will start the 
                 timer and specify which led should go off */
                LED_array[0] = 2;

            }
            break;

        case 1:
            if (state == 1) {
                LED1_SetHigh();
                LED_array[1] = 1;
            }
            else if (state == 0) {
                LED1_SetLow();
                LED_array[1] = 0;
            }
            else if (state == 2) {
                /*Setup timer here for interupts or enable interupt flag for timer.
                 Thinking that the function will be like 
                 Blinkstart(lednum) which will start the 
                 timer and specify which led should go off */
                LED_array[1] = 2;

            }
            break;
        case 2:
            if (state == 1) {
                LED2_SetHigh();
                LED_array[2] = 1;
            }
            else if (state == 0) {
                LED2_SetLow();
                LED_array[2] = 0;
            }
            else if (state == 2) {
                /*Setup timer here for interupts or enable interupt flag for timer.
                 Thinking that the function will be like 
                 Blinkstart(lednum) which will start the 
                 timer and specify which led should go off */
                LED_array[2] = 2;

            }


            break;

        case 3:
            if (state == 1) {
                LED3_SetHigh();
                LED_array[3] = 1;
            }
            else if (state == 0) {
                LED3_SetLow();
                LED_array[3] = 0;
            }

            else if (state == 2) {
                /*Setup timer here for interupts or enable interupt flag for timer.
                 Thinking that the function will be like 
                 Blinkstart(lednum) which will start the 
                 timer and specify which led should go off */
                LED_array[3] = 2;

            }

            break;
        case 4:
            if (state == 1) {
                LED4_SetHigh();
                LED_array[4] = 1;
            }
            else if (state == 0) {
                LED4_SetLow();
                LED_array[4] = 0;
            }

            else if (state == 2) {
                /*Setup timer here for interupts or enable interupt flag for timer.
                 Thinking that the function will be like 
                 Blinkstart(lednum) which will start the 
                 timer and specify which led should go off */
                LED_array[4] = 2;
            }

            break;
        case 5:
            if (state == 1) {
                LED5_SetHigh();
                LED_array[5] = 1;
            }
            else if (state == 0) {
                LED5_SetLow();
                LED_array[5] = 0;
            }

            else if (state == 2) {
                /*Setup timer here for interupts or enable interupt flag for timer.
                 Thinking that the function will be like 
                 Blinkstart(lednum) which will start the 
                 timer and specify which led should go off */
                LED_array[5] = 2;

            }


            break;
    }
}

// Added another function with a different set of arguments.
// This function is the same as the first SetLEDOut() function 
// However the difference is 
void SetLEDOut(int lednum, bool state, int time) {
    switch (lednum) {
        case 0:
            if (state == 1) {
                LED0_SetHigh();
                LED_array[0] = 1;
            }
            else if (state == 0) {
                LED0_SetLow();
                LED_array[0] = 0;
            }

            else if (state == 2) {
                /*Setup timer here for interupts or enable interupt flag for timer.
                 Thinking that the function will be like 
                 Blinkstart(lednum,timer) which will start the 
                 timer and specify which led should go off how long does it take to switch states.*/
                LED_array[0] = 2;

            }
            break;

        case 1:
            if (state == 1) {
                LED1_SetHigh();
                LED_array[1] = 1;
            }
            else if (state == 0) {
                LED1_SetLow();
                LED_array[1] = 0;
            }
            else if (state == 2) {
                /*Setup timer here for interupts or enable interupt flag for timer.
                 Thinking that the function will be like 
                 Blinkstart(lednum,timer) which will start the 
                 timer and specify which led should go off how long does it take to switch states.*/
                LED_array[1] = 2;

            }
            break;
        case 2:
            if (state == 1) {
                LED2_SetHigh();
                LED_array[2] = 1;
            }
            else if (state == 0) {
                LED2_SetLow();
                LED_array[2] = 0;
            }
            else if (state == 2) {
                /*Setup timer here for interupts or enable interupt flag for timer.
                 Thinking that the function will be like 
                 Blinkstart(lednum,timer) which will start the 
                 timer and specify which led should go off how long does it take to switch states.*/
                LED_array[2] = 2;

            }


            break;

        case 3:
            if (state == 1) {
                LED3_SetHigh();
                LED_array[3] = 1;
            }
            else if (state == 0) {
                LED3_SetLow();
                LED_array[3] = 0;
            }

            else if (state == 2) {
                /*Setup timer here for interupts or enable interupt flag for timer.
                 Thinking that the function will be like 
                 Blinkstart(lednum,timer) which will start the 
                 timer and specify which led should go off how long does it take to switch states.*/
                LED_array[3] = 2;

            }

            break;
        case 4:
            if (state == 1) {
                LED4_SetHigh();
                LED_array[4] = 1;
            }
            else if (state == 0) {
                LED4_SetLow();
                LED_array[4] = 0;
            }

            else if (state == 2) {
                /*Setup timer here for interupts or enable interupt flag for timer.
                 Thinking that the function will be like 
                 Blinkstart(lednum,timer) which will start the 
                 timer and specify which led should go off how long does it take to switch states.*/
                LED_array[4] = 2;
            }

            break;
        case 5:
            if (state == 1) {
                LED5_SetHigh();
                LED_array[5] = 1;
            }
            else if (state == 0) {
                LED5_SetLow();
                LED_array[5] = 0;
            }

            else if (state == 2) {
                /*Setup timer here for interupts or enable interupt flag for timer.
                 Thinking that the function will be like 
                 Blinkstart(lednum,timer) which will start the 
                 timer and specify which led should go off how long does it take to switch states.*/
                LED_array[5] = 2;

            }


            break;
    }
}
// Gets the LED state of the desired led number the state can currently be on(1) off(0) or blinking(2))
  int GetLEDState(int lednum)
  {
      return LED_array[lednum];
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



