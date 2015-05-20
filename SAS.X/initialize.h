/* 
 * File:   initialize.h
 * Author: Igor
 *
 * Created on March 26, 2015, 9:07 AM
 */

#ifndef INITIALIZE_H
#define	INITIALIZE_H

extern void delay(int ms);
//extern int receiveArray[20];
void initialize(void);
void oscillator(void);
void timerOne(void);
void initUART1(void);
extern void UART_init(void);
void PinIO(void);

void timerTwo(void);
extern unsigned char Receive_peek(void);
extern int Receive_available(void);
extern unsigned char Receive_get(void);
extern void Send_put(unsigned char _data);
extern void begin(int * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void),int (*stuffavailable)(void), unsigned char (*stuffpeek)(void));


#endif	/* INITIALIZE_H */

