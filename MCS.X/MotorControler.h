/* 
 * File:   MotorControler.h
 * Author: Rick
 *
 * Created on May 12, 2015, 1:09 AM
 */

#ifndef MOTORCONTROLER_H
#define	MOTORCONTROLER_H

#include <stdbool.h>

typedef enum Directionality
{
  forward = 1,
  backward = 2,
  stop = 3
}dirr;

void SetMotor(int speed, enum Directionality direction);
void SetRegen(int amount);
void Regen(bool enable);

#endif	/* MOTORCONTROLER_H */

