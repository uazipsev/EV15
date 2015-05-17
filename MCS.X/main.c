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
           //PotSetpoint(i);
           Delay(250);
           INDICATOR = !INDICATOR;
        }
        */
        Delay(250);
       INDICATOR = 1;
        Delay(250);
       INDICATOR = 0;
       Delay(250);
    }

    return (EXIT_SUCCESS);
}

