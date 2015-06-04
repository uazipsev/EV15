/* 
 * File:   interrupt_handler.h
 * Author: Igor
 *
 * Created on March 28, 2015, 11:36 AM
 */

#ifndef INTERRUPT_HANDLER_H
#define	INTERRUPT_HANDLER_H
bool PrepSend;

bool ADCSamp=true;
unsigned int ADCTime;
volatile unsigned int LEDtime=0,talkTime=0;
volatile unsigned int ADCbuffer[6];
bool ADCDataReady = false;
#endif	/* INTERRUPT_HANDLER_H */

