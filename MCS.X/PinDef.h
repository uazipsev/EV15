/* 
 * File:   PinDef.h
 * Author: Rick
 *
 * Created on May 12, 2015, 12:00 AM
 */

#ifndef PINDEF_H
#define	PINDEF_H

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
#define Analog_Relay PORTAbits.RA0

/*
 *    12 DC/DC
 */
#define DC12EN PORTAbits.RA10



#endif	/* PINDEF_H */

