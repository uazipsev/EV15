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

void SetLEDOut(int lednum)
{
  switch (lednum)
  {
      case 0:
          LED0_Toggle();
          break;
      case 1:
          LED1_Toggle();
          break;
      case 2:
          LED2_Toggle();
          break;
      case 3:
          LED3_Toggle();
          break;
      case 4:
          LED4_Toggle();
          break;
      case 5:
          LED5_Toggle();
          break;
  }
}


void ReadButtonState(int btnnum)
{
  switch (btnnum)
  {
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

bool GetButtonState(int btnnum)
{
    return butnarray[btnnum-1];
}





