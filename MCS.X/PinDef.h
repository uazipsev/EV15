/* 
 * File:   PinDef.h
 * Author: Rick
 *
 * Created on May 12, 2015, 12:00 AM
 */

#ifndef PINDEF_H
#define	PINDEF_H

#define true 1
#define false 0

/*
 *  RS485 Flow control
 */
#define RS_RE_DE PORTBbits.RB0

/*
 *    LED :)
 */
#define INDICATOR _LATB1

/*
 *   Motor Control Pins
 */
#define FORWARD PORTCbits.RC1
#define REVERSE PORTCbits.RC2
#define BRAKE   PORTAbits.RA8
#define PROGEN  PORTBbits.RB4
#define REGENEN PORTAbits.RA4

/*
 *   DigiPot control lines
 */
#define DIGI_CS     PORTBbits.RB15
#define DIGI_INC    PORTBbits.RB14
#define DIGI_UP_DN  PORTAbits.RA7

/*
 *    Relay control 
 */
#define Analog_Relay _LATA0
#define Analog_Relay_Port PORTAbits.RA0

/*
 *    12 DC/DC
 */
#define DC12EN _LATA10

/*
 *    FAN PWM
 */
#define FAN _LATB5


#endif	/* PINDEF_H */

