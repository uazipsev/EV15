/* 
 * File:   main.c
 * Author: Rick and Zac
 *
 * Created on May 11, 2015, 11:19 PM
 */

#include "main.h"
#include "SlaveAddressing.h"

extern void updateTimers();

extern int BVolts[NUMSLAVES][BATTPERSLAVE];
extern int BTemps[NUMSLAVES][TEMPPERSLAVE];
/*
 * 
 */

int main(int argc, char** argv) {
    Setup();
    int l = 0, j = 0;
    for (l = 0; l < NUMSLAVES; l++) {
        for (j = 0; j < BATTPERSLAVE; j++) {
            BVolts[l][j] = 3000;
        }
        for (j = 0; j < TEMPPERSLAVE; j++) {
            BTemps[l][j] = 70;
        }
    }
    while (1) {
        updateTimers();
        ledDebug();
        updateComms();
    }

    return (EXIT_SUCCESS);
}

