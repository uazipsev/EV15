/* 
 * File:   main.h
 * Author: Igor
 *
 * Created on March 26, 2015, 5:39 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#define ON         0
#define OFF        1
#define INDICATOR1 LATEbits.LATE5
#define INDICATOR2 LATEbits.LATE6
#define INDICATOR3 LATGbits.LATG7
#define INDICATOR4 LATGbits.LATG8
#define WATCHDOG   LATEbits.LATE7

#define HORIZONTAL_BEACON       0
#define RIGHT_BEACON            0
#define VERTICAL_BEACON         1
#define LEFT_BEACON             1

#define LEFT_CAMERA             0
#define RIGHT_CAMERA            1


    //ADDRESSING FOR ROBOT
#define CONTROL_ADDRESS              5
#define NAVIGATION_ADDRESS           1
#define PIC_ADDRESS                  4
#define MOTOR_ADDRESS                6
#define LED_ADDRESS                  2
#define POWER_ADDRESS	             3

//FROM NAV
#define ROBOT_MOVING		         1
#define WII_SUBSYSTEM_MODE           2    //MODES INCLUDE: TRIG=0, LEFT_BEACON_ANGLES=1, RIGHT_BEACON_ANGLES=2, CAMERA_OVERRIDE_BEACON_ANGLES=3
#define WII_LEFT_CAMERA_MODE         3    //MODES 3 and 4 only used for WII_SUBSYSTEM_MODE 3
#define WII_RIGHT_CAMERA_MODE        4            //0=LEFT_BEACON 1=RIGHT_BEACON
//TO NAV
#define ENCODER_R_NAVIGATION     	 5
#define ENCODER_L_NAVIGATION        6
#define ENCODER_SPEED_R_NAVIGATION  7
#define ENCODER_SPEED_L_NAVIGATION  8

#define ENCODER_R_CONTROL     	 11
#define ENCODER_L_CONTROL        12
#define ENCODER_SPEED_R_CONTROL  13
#define ENCODER_SPEED_L_CONTROL  14



typedef enum WII_state{
    TRIG=0, LEFT_BEACON_ANGLES=1, RIGHT_BEACON_ANGLES=2, CAMERA_OVERRIDE_BEACON_ANGLES=3, CONTINUOUS_AQUISITION=4, MAXENUMS=5
}states;

int receiveArray[20];

extern unsigned int angleSet[2];
extern int beaconCentered[2][2];
extern int numberSweeps[2];
extern bool beaconSeen[2];
extern void initialize(void);
extern void initCamera(int cameraNumber);
extern void doOverrideBeaconAcquisition(int cLBeacon, int cRBeacon);
extern void doHorizontalBeaconAcquisition();
extern void doVerticalBeaconAcquisition();
extern void doXYAcquisition();
extern void doContinuousAcquisition();

extern void resetWiiBeaconStates();
extern bool receiveData();
extern void sendData(unsigned char whereToSend);
extern void ToSend(const unsigned char where, const unsigned int what);


extern void sendEncoderValues();
extern int cameraReady(int cameraNumber);
extern void readCamera(int cameraNumber);
volatile unsigned int wiiTime = 0;
#endif	/* MAIN_H */

