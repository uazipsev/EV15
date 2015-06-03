/* 
 * File:   main.c
 * Author: Rick
 *
 * Created on May 11, 2015, 11:19 PM
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <xc.h>
#include "main.h"
#include "PinDef.h"

/*
 * 
 */
int main(int argc, char** argv) {
    Setup();
    while(1)
    {
        if(receiveData())
            INDICATOR ^= 1;
    }

    return (EXIT_SUCCESS);
}

