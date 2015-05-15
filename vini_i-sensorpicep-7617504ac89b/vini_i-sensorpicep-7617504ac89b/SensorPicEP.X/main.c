
#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "main.h"

//




enum WII_state currentState = CONTINUOUS_AQUISITION;

int leftCameraTarget, rightCameraTarget;

void delay(int ms);

int main(void) {
    initialize();
    initCamera(0);
    initCamera(1);
    delay(50);
    while (1) {

       

        while (receiveData()) {
            if (currentState != receiveArray[WII_SUBSYSTEM_MODE]) {
                currentState = receiveArray[WII_SUBSYSTEM_MODE];
                resetWiiBeaconStates();
            }
            leftCameraTarget = receiveArray[WII_LEFT_CAMERA_MODE];
            rightCameraTarget = receiveArray[WII_RIGHT_CAMERA_MODE];
            if (receiveArray[ROBOT_MOVING] != 0) {
                receiveArray[ROBOT_MOVING] = 0;
                resetWiiBeaconStates();
            }
        }
        static bool leftReady=true, rightReady=true;
        //static int cameraStatusLeft, cameraStatusRight;

        if(cameraReady(LEFT_CAMERA)==1){
            leftReady=true;
        }
        else if (cameraReady(LEFT_CAMERA)==2){
            readCamera(LEFT_CAMERA);
            INDICATOR3^=1;
        }
        else if (cameraReady(LEFT_CAMERA)==0){
            leftReady=false;
        }

        if(cameraReady(RIGHT_CAMERA)==1){
            rightReady=true;
        }
        else if (cameraReady(RIGHT_CAMERA)==2){
            readCamera(RIGHT_CAMERA);
            INDICATOR4^=1;
        }
        else if (cameraReady(RIGHT_CAMERA)==0){
         rightReady=false;
        }


        if (wiiTime > 150) {
            if(leftReady && rightReady){
            switch (currentState) {
                case TRIG:
                    doXYAcquisition();
                    break;
                case LEFT_BEACON_ANGLES:
                    doVerticalBeaconAcquisition();
                    break;
                case RIGHT_BEACON_ANGLES:
                    doHorizontalBeaconAcquisition();
                    break;
                case CAMERA_OVERRIDE_BEACON_ANGLES:
                    doOverrideBeaconAcquisition(leftCameraTarget, rightCameraTarget);
                    break;
                case CONTINUOUS_AQUISITION:
                    doContinuousAcquisition();
                    break;
                case MAXENUMS:

                    break;
            }
            readCamera(LEFT_CAMERA);
            readCamera(RIGHT_CAMERA);
            wiiTime=0;
            leftReady=false;
            rightReady=false;
            }

        }
    }
}
