/* 
 * File:   main.h
 * Author: User
 *
 * Created on May 28, 2015, 10:47 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

extern void updateComms();

extern void Delay(int ms);
extern void Setup(void);

extern volatile unsigned int time;

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

