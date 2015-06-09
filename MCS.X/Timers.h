/* 
 * File:   Timers.h
 * Author: User
 *
 * Created on June 7, 2015, 5:52 PM
 */

#ifndef TIMERS_H
#define	TIMERS_H

#ifdef	__cplusplus
extern "C" {
#endif

    void timerTwo(void);
    void timerOne(void);
    volatile unsigned int talkTime, LEDtime,safetyTime;


#ifdef	__cplusplus
}
#endif

#endif	/* TIMERS_H */

