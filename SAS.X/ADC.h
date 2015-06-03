/* 
 * File:   ADC.h
 * Author: Rick
 *
 * Created on May 19, 2015, 2:11 AM
 */

#ifndef ADC_H
#define	ADC_H

void initADC(void);
void GetADC(void);
void SetADC(void);

void handleADCValues();
extern volatile unsigned int ADCbuffer[6];
unsigned int throttle1,throttle2,brake;
#endif	/* ADC_H */

