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
#include "PinDef.h"
#include "horn.h"

/*
 * 
 */
int main(int argc, char** argv) {
    Setup();
    int x = 0;
    while(1)
    {
       x = 0;
       Delay(1000);
       INDICATOR = 1;
       BRAKELT = 1;
       Delay(1000);
       INDICATOR = 0;
       BRAKELT = 0;
       RTD(10);
    }

    return (EXIT_SUCCESS);
}

