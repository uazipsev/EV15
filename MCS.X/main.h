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
    extern void sendData(unsigned char whereToSend);
    extern bool receiveData();
    extern void ToSend(const unsigned char where, const unsigned int what);
    extern void Setup(void);
    extern void Delay(int wait);
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

