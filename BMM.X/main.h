/* 
 * File:   main.h
 * Author: User
 *
 * Created on May 27, 2015, 8:36 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <xc.h>
#include "PinDef.h"
#include "ADDRESSING.h"

    extern void Setup(void);
    extern void Delay(int wait);

    extern void updateComms();
    extern volatile unsigned int LEDtime;

    void ledDebug() {
        if (LEDtime > 2) {
            INDICATOR = !INDICATOR;
            LEDtime = 0;
        }
    }

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

