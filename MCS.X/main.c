/* 
 * File:   main.c
 * Author: Rick
 *
 * Created on May 11, 2015, 11:19 PM
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include "PinDef.h"
#include "main.h"
#include "Communications.h"
#include "ADDRESSING.h"
#include "Function.h"
/*
 * 
 */
int main(int argc, char** argv) {
    Setup();
    //RS485 direction
    LATBbits.LATB13 = 0;
    //DAC relay
    LATAbits.LATA0 = 1;
    
    while (1) {
        updateComms();
        ledDebug();
    }

    return (EXIT_SUCCESS);
}

