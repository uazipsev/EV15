/* 
 * File:   main.h
 * Author: User
 *
 * Created on May 27, 2015, 5:30 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

void ledDebug();
void prepAndSendData();
extern bool Transmit_stall;
extern volatile unsigned int talkTime;
extern volatile unsigned int LEDtime;
extern volatile int receiveArray[20];

extern void Delay(int ms);
extern void Setup(void);

extern void sendData(unsigned char whereToSend);
extern bool receiveData();
extern void ToSend(const unsigned char where, const unsigned int what);
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

