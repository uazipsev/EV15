/* 
 * File:   main.c
 * Author: Rick
 *
 * Created on May 11, 2015, 11:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "xc.h"
#include "PinDef.h"
#include "ADDRESSING.h"
#include "main.h"

void setMCSOutputs(unsigned int t1, unsigned int t2, unsigned int b);
bool checkSASInputs(unsigned int t1, unsigned int t2, unsigned int b);

int main(int argc, char** argv) {
    Setup();
    Delay(1000);
    while (1) {
        ledDebug();
        updateComms();
        //DDS Process Data
        if (seekButtonChange()) {
            changeLEDState(IMD_INDICATOR, !buttonArray[1]);
            changeLEDState(DASH_LED, !buttonArray[2]);
            changeLEDState(BMS_LED, !buttonArray[3]);
        }


    }
    return (EXIT_SUCCESS);
}

