/* 
 * File:   Functions.h
 * Author: Rick
 *
 * Created on May 19, 2015, 1:33 AM
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#include <stdbool.h>

#ifndef __DELAY_H
#define FOSC  72000000LL  // clock-frequecy in Hz with suffix LL (64-bit-long), eg. 32000000LL for 32MHz
#define FCY       (FOSC/2)  // MCU is running at FCY MIPS
#define delay_us(x) __delay32(((x*FCY)/1000000L)) // delays x us
#define delay_ms(x) __delay32(((x*FCY)/1000L))  // delays x ms
#define __DELAY_H 1
#include <libpic30.h>
#endif

extern void Delay(int ms);
void Setup(void);
void PinSetMode(void);
void timerOne(void);
//void initUART1(void);
extern void UART_init(void);

extern volatile int receiveArray[20];
void timerTwo(void);
extern unsigned char Receive_peek(void);
extern int Receive_available(void);
extern unsigned char Receive_get(void);
extern void Send_put(unsigned char _data);
extern void begin(volatile int * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void),int (*stuffavailable)(void), unsigned char (*stuffpeek)(void));



#endif	/* FUNCTIONS_H */

