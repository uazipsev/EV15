/* 
 * File:   Functions.h
 * Author: Rick
 *
 * Created on May 17, 2015, 2:16 AM
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#ifndef __DELAY_H
#define FOSC  7372800LL  // clock-frequecy in Hz with suffix LL (64-bit-long), eg. 32000000LL for 32MHz
#define FCY       (FOSC/2)  // MCU is running at FCY MIPS
#define delay_us(x) __delay32(((x*FCY)/1000000L)) // delays x us
#define delay_ms(x) __delay32(((x*FCY)/1000L))  // delays x ms
#define __DELAY_H 1
#include <libpic30.h>
#endif

extern void Delay(int wait);
extern void Setup();
extern void initInterrupts(void);

#endif	/* FUNCTIONS_H */

