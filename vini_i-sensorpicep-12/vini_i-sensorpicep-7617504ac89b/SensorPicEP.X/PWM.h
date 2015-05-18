/* 
 * File:   PWMCode.h
 * Author: Keith
 *
 * Created on January 3, 2015, 3:43 PM
 */

#ifndef PWM_H
#define	PWM_H

#define SERVO_MAX               1450
#define SERVO_MIN               350

void initPWM1(int offset_correction);
void setAngle1(unsigned int update_angle);
unsigned int presentAngle1(void);

void initPWM2(int offset_correction);
void setAngle2(unsigned int update_angle);
unsigned int presentAngle2(void);

#endif	/* PWM_H */

