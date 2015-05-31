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
#include "horn.h"
#include "ADDRESSING.h"
#include "main.h"


void ledDebug();

/*
 * 
 */
int main(int argc, char** argv) {
    Setup();
    Delay(500);
    while (1) {
        ledDebug();
        updateComms();
       
    }

    return (EXIT_SUCCESS);
}

void ledDebug() {

    if (time > 1000) {
        INDICATOR ^= 1;
        time = 0;
    }

}
