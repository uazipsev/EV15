/* 
 * File:   pwm.h
 * Author: Rick
 *
 * Created on May 21, 2015, 12:19 AM
 */

#ifndef PWM_H
#define	PWM_H

extern void PWM_Init(void);
void Timmer2Init(void);
extern void PWM1update(int output);
extern void PWM2update(int output);

#endif	/* PWM_H */

