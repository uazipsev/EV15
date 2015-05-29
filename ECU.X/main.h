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

void requestSASData();
extern void sendData(unsigned char whereToSend);
extern bool receiveData();
extern void ToSend(const unsigned char where, const unsigned int what);
extern void Delay(int ms);
extern void Setup(void);


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

