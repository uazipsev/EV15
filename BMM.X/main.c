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

/*
 * 
 */
int main(int argc, char** argv) {
    Setup();
    int x = 0;
    while(1)
    {
       x = 0;
       Delay(100);
       INDICATOR = 1;
       Delay(100);
       INDICATOR = 0;
    }

    return (EXIT_SUCCESS);
}

