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
#define INDICATOR _LATE13

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
 *    HORN
 */
#define HORN_EN _LATB9

/*
 *   Brake Light
 */
#define BRAKELT _LATB6


#endif	/* PINDEF_H */

