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

#define BMS_LED        5
#define ACTIVE_LED     3
#define IMD_INDICATOR  2
#define START_BUTTON   2
#define AUX_BUTTON     1


    extern unsigned int throttle1, throttle2, brake;
    void updateBrakeLight();
    void updateECUState();
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
    extern volatile unsigned int BootTimer;
    extern void updateComms();
    extern void Delay(int ms);
    extern void Setup(void);


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

