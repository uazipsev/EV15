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
#include "ADDRESSING.h"



/*
 * 
 */
int main(int argc, char** argv) {
    Setup();
    //int x = 0;
    LATBbits.LATB13=0;
    while(1)
    {
        if(receiveData())
        {
            LATBbits.LATB13 =1;
            Delay(2);
            ToSend(RESPONSE_ADDRESS,MCS_ADDRESS);
            sendData(ECU_ADDRESS);
            Delay(3);
            LATBbits.LATB13 =0;
        }
       //x = 0;
       //Delay(100);
       //INDICATOR = 1;
       //Delay(100);
       //INDICATOR = 0;
    }

    return (EXIT_SUCCESS);
}

