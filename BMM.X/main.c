/* 
 * File:   main.c
 * Author: Rick and Zac
 *
 * Created on May 11, 2015, 11:19 PM
 */

#include "main.h"

/*
 * 
 */

int main(int argc, char** argv) {
    Setup(); 
    while (1) {
        ledDebug();
        updateComms();
    }

    return (EXIT_SUCCESS);
}

