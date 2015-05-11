/* 
 * File:   Shift595.h
 * Author: Rick
 *
 * Created on May 11, 2015, 1:44 AM
 */

#ifndef SHIFT595_H
#define	SHIFT595_H

#define num_of_595s 3
#define RegPins num_of_595s * 8

int registers[RegPins];

extern void StartUp595();
extern void SetPin595(int Reg, int pin, int value);
extern void Clear595();
extern void writeRegisters();


#endif	/* SHIFT595_H */

