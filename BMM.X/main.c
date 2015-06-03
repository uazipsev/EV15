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
#include "ADDRESSING.h"

/*
 * 
 */
int main(int argc, char** argv) {
    Setup();
    while(1)
    {
        if(receiveData()){
            LATBbits.LATB13   = 1;
            
            ToSend(RESPONSE_ADDRESS,BMM_ADDRESS);
            Delay(4);
            sendData(ECU_ADDRESS);
            Delay(5);

            LATBbits.LATB13   = 0;
            INDICATOR ^= 1;
        }
    }

    return (EXIT_SUCCESS);
}

