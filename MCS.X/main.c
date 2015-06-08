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

/*
 * 
 */
int main(int argc, char** argv) {
    Setup();
    LATBbits.LATB13=0;
    LATAbits.LATA0=1;

    SetMotor(0,1);
    SetRegen(0);
    while(1)
    {
        updateComms();
        ledDebug();       
    }

    return (EXIT_SUCCESS);
}

