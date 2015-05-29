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

/*
 * 
 */
int main(int argc, char** argv) {
    Setup();
    Delay(50);
    requestSASData();
    while (1) {
        if (receiveData()) {
            Delay(50);
            requestSASData();
            BRAKELT ^= 1;
        } else {
            static int counter = 0;
            counter++;
            if (counter > 100) {
                requestSASData();
                counter = 0;
            }
        }
        Delay(1);
        //INDICATOR ^= 1;
        //Delay(5);
        //       BRAKELT = 1;
        //       Delay(1000);
        //       INDICATOR = 0;
        //       BRAKELT = 0;
        //       RTD(100);
    }

    return (EXIT_SUCCESS);
}

void requestSASData() {
    RS485_1_Direction = TALK;
    Delay(1);
    ToSend(0, 0);
    sendData(SAS_ADDRESS);
    Delay(2);
    RS485_1_Direction = LISTEN;
}