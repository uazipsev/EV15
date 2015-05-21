/* 
 * File:   PinDef.h
 * Author: Rick
 *
 * Created on May 19, 2015, 1:18 AM
 */

#ifndef PINDEF_H
#define	PINDEF_H


#define ON         0
#define OFF        1

extern bool receiveData();
extern void sendData(unsigned char whereToSend);
extern void ToSend(const unsigned char where, const unsigned int what);

//extern void sendEncoderValues();
#define LED _LATB9
#define LED_Port PORTBbits.RB9
#define WDI _LATB12
#define WDI_Port PORTBbits.RB12
#define RS485 _LATC8
#define RS485_Port PORTCbits.RC8

#endif	/* PINDEF_H */

