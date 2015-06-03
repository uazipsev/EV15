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
#include "ADDRESSING.h"
#include "main.h"
#define TRIP_THROTTLE 10
#define TRIP_BRAKE    10
int main(int argc, char** argv) {
    Setup();
    Delay(500);
    while (1) {
        ledDebug();
        updateComms();
        //DDS Process Data
        if(seekButtonChange()){
            if(buttonArray[START_BUTTON]){
                changeLEDState(START_LED,1);     
            }
        }
        //SAS Process Data
        if(checkSASInputs(throttle1,throttle2,brake)){
            setMCSOutputs(throttle1,throttle2,brake);
        }

    }
    return (EXIT_SUCCESS);
}

bool checkSASInputs(unsigned int t1, unsigned int t2, unsigned int b){
    //throttle consistency check
    if(!((t1+(t1/10)>t2)&&(t1-(t1/10)<t2))){
        return false;
    }
    //Brake vs. throttle safety
    if(((t1+t2/2)>TRIP_THROTTLE)&&(b>TRIP_BRAKE)){
        return false;
    }
    return true;

}
void setMCSOutputs(unsigned int t1, unsigned int t2, unsigned int b){


}