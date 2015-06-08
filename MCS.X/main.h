/* 
 * File:   main.h
 * Author: User
 *
 * Created on May 27, 2015, 8:48 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif
    extern void updateComms();
    extern void Setup(void);
    extern void Delay(int wait);
    extern volatile unsigned int LEDtime;

    void ledDebug() {
        if (LEDtime > 1000) {
            LEDtime = 0;

            INDICATOR ^= 1;
        }

    }
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

