/* 
 * File:   main.c
 * Author: Rick
 *
 * Created on May 11, 2015, 11:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include "Function.h"
#include "DigiPot.h"
#include "PinDef.h"

/*
 * 
 */
int main(int argc, char** argv) {
    Setup();
    INDICATOR = 1;
    int i;
    while(1)
    {
        /*
        for(i =0;i<32;i++)
        {
           PotSetpoint(i);
           Delay(400);
           INDICATOR = !INDICATOR;
        }
        */
       Delay(2000);
       INDICATOR = 1;
       _LATB5 = 1;
       //DC12EN = 1;   //Turns it off
       //Analog_Relay = 1;
       Delay(2000);
       INDICATOR = 0;
       _LATB5 = 0;
       //DC12EN = 0;   //Turns it on
       //Analog_Relay = 0;
    }

    return (EXIT_SUCCESS);
}

