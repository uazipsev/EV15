/* 
 * File:   Main.c
 * Author: Richard Johnson & Z. Killburn
 *
 * Created on May 16, 2015, 11:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "Functions.h"
#include "Config_Bits.h"
#include "PinDef.h"


/*
 * 
 */
int main(int argc, char** argv) {
    Setup();

    int i;
    while(1)
    {
        /*
        for(i =0;i<32;i++)
        {
           //PotSetpoint(i);
           Delay(250);
           INDICATOR = !INDICATOR;
        }
        */
        Delay(250);
       INDICATOR = 1;
        Delay(500);
       INDICATOR = 0;
       Delay(500);
    }
    return (EXIT_SUCCESS);
}


/*

 #include <stdlib.h>
#include <xc.h>
#include <libpic30.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "definitions.h"
#include "methods.h"
#include "variables.h"
#include "initSystems.h"

#include "commSystems.h"
#include "interrupts.h"


int readings[20];
static int ADCT = 0;
#define ADCTime 10000

int main(int argc, char** argv) {
    initPins();
    oscillatorInit();
    initInterrupts();
    setupCommData();
    initUARTS();
    initADC();
    initSpeeds();
    initRS485Direction();
    delay_5ms();

    while (1) {
        readADCValues();
        getSpeedSensorValue();
        brakeLightCheck();
        listenECU();
        toggleLED();
    }
    return (EXIT_SUCCESS);
}

void listenECU() {
    if (packetReady) {
        IEC0bits.AD1IE = 1;
        toggleECUdirection();
        delay_5ms();
        switch (inputCmd) {
            case 1:
                writeCommTB();
                break;
            case 3:
                writeCommDataPacket();
                clearPulseCounter();
                break;
        }
        DELAY_100uS;
        DELAY_100uS;
        DELAY_100uS;
        DELAY_100uS;
        DELAY_100uS;
        DELAY_100uS;
        DELAY_100uS;
        inputCmd = 0;
        packetReady = 0;
        toggleECUdirection();
    }
}

void toggleLED() {
    if (LEDTime > LEDT) {
        LED = !LED;
        LEDTime = 0;
        //        putStrUSB((char*)"$$START$$");
        //        putByteUSB(13);
        //        putStrUSB((char*)"Throttle1: ");


        // $$ serial output for debugging
        //        for(i=1;i<=4;i++){
        //            putByteUSB(i);
        //            putIntUSB(pulseCount[i]);
        //        }
        //
//        putByteUSB(0xEC);
//        putIntUSB(throttle1);
//        putIntUSB(throttle2);
//        putIntUSB(brake1);
//        putIntUSB(brake2);
        //        putIntUSB(readings[2]);
        //        putIntUSB(readings[3]);
        //        putIntUSB(readings[5]);
        //putIntUSB(readings[4]);   4 not in use
        //putIntUSB(readings[6]);   6 not in use or not populated
        //        putStrUSB((char*)"$$$END$$$");
        //        putByteUSB(13);



        IEC0bits.AD1IE = 1;
    } else LEDTime++;
}

void readADCValues() {
    if ((ADCdata == 1)) {
        for (i = 0; i < 6; i++) {
            DELAY_100uS;
            readings[i] = buffer[i];
        }
        ADCdata = 0;

        //        throttle1=readings[2];
        //        throttle2=readings[3];

        //Check values for out of range low to avoid rollover

        throttle1 = (unsigned int) (readings[1] / 9) - 54;
        throttle2 = (unsigned int) ((2095 - readings[5])*0.2298);


        if ((throttle1 < 3)||(throttle1>200)) {
            throttle1 = 0;
        } else if (throttle1 > 100) {
            throttle1 = 100;
        } else if (throttle1 > 10) {
            throttle1 = throttle1 - 4;
        }
        if ((throttle2 < 4)||(throttle2>200)) {
            throttle2 = 0;
        } else if (throttle2 > 100) {
            throttle2 = 100;
        }

         brake1 = readings[3];
//         brake2=readings[2];
//        brake1 = (980 - readings[3]);
//        if ((brake1<45) || (brake1 > 900)) {
//            brake1 = 0;
//        }
//        brake1=brake1/9;
//        if(brake1>100){
//            brake1=100;
//        }
        brakeLightCheck();

        brake2 = readings[2] - 350;
        if ((brake2 < 0) || (brake2 > 1200)) {
            brake2 = 0;
        }
        brake2=brake2/8;
        if(brake2>100){
            brake2=100;
        }


        //Change all 0-100's to 0-4095
//        throttle1 = (unsigned int) throttle1 * 40.95;
//        throttle2 = (unsigned int) throttle2 * 40.95;
//        brake1 = (unsigned int) (brake1 * 40.95);
//        brake2 = (unsigned int) (brake2 * 40.95);
    }
}

void brakeLightCheck() {
    if ((brake2) > 15) {
        BrakeLight = 1;
    } else
        BrakeLight = 0;
}

 */
