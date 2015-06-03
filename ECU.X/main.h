/* 
 * File:   main.h
 * Author: Zac Kilburn
 *
 * Created on May 28, 2015, 10:47 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif


#define START_BUTTON 0
#define START_LED  0
#define DASH_LED2  1

    extern int buttonArray[8];
    extern bool seekButtonChange();
    extern void changeLEDState(int LED, bool state);
    extern volatile unsigned int time;

    void ledDebug() {
        if (time > 1000) {
            INDICATOR ^= 1;
            time = 0;
        }
    }

    extern void updateComms();
    extern void Delay(int ms);
    extern void Setup(void);

    unsigned int throttle1,throttle2,brake;

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

