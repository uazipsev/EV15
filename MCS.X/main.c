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

extern void SetDAC1(unsigned int value);
extern void SetDAC2(unsigned int value);
extern void i2cUpdate();
/*
 * 
 */
int main(int argc, char** argv) {
    Setup();
    //RS485 direction
    LATBbits.LATB13 = 0;
    //DAC relay
    LATAbits.LATA0 = 1;
    //Motor 12 V 
    LATAbits.LATA10=1;
    //Set outputs to motor controller to 0's
    SetDAC1(0);
    SetDAC2(0);
    while (1) {
        updateComms();
        ledDebug();
        //I2Cupdate();
    }

    return (EXIT_SUCCESS);
}

