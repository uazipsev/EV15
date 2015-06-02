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

int main(int argc, char** argv) {
    Setup();
    Delay(500);
    while (1) {
        ledDebug();
        updateComms();
        //DDS Process Data
        if(seekButtonChange()){
            if(buttonArray[START_BUTTON]){
                changeLEDState(START_LED,1);     
            }
        }
        //SAS Process Data

    }
    return (EXIT_SUCCESS);
}
