/* 
 * File:   Battery.h
 * Author: Rick
 *
 * Created on March 25, 2015, 4:01 AM
 */

#ifndef BATTERY_H
#define	BATTERY_H

extern char Battery_Fault();
extern void Battery_Read();
extern void Battery_Filter();
extern void Battery_Convert();
extern float Battery_Get(int channelnum);


#endif	/* BATTERY_H */

