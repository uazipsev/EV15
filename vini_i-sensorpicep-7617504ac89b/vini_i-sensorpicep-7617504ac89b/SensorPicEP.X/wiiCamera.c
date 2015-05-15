
#include <xc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "wiiCamera.h"
#include "PWM.h"
#define ON         0
#define OFF        1
#define INDICATOR1 LATEbits.LATE5
#define INDICATOR2 LATEbits.LATE6
#define INDICATOR3 LATGbits.LATG7
#define INDICATOR4 LATGbits.LATG8
#define WATCHDOG   LATEbits.LATE7

bool vertical = true;
unsigned char camera = 0xB0;
unsigned char data_address = 0x36;

int isAbout(int compareThis, int toThis, int range);
unsigned char read(int cameraNumber);

void resetWiiBeaconStates() {
    vertical = true;
    beaconSeen[LEFT_CAMERA] = 0;
    beaconSeen[RIGHT_CAMERA] = 0;
    beaconCentered[LEFT_CAMERA][LEFT_BEACON] = 0;
    beaconCentered[LEFT_CAMERA][RIGHT_BEACON] = 0;
    beaconCentered[RIGHT_CAMERA][LEFT_BEACON] = 0;
    beaconCentered[RIGHT_CAMERA][RIGHT_BEACON] = 0;
    Camera[LEFT_CAMERA].result = 0;
    Camera[RIGHT_CAMERA].result = 0;
    beaconAngle[LEFT_CAMERA][LEFT_BEACON] = 0;
    beaconAngle[LEFT_CAMERA][RIGHT_BEACON] = 0;
    beaconAngle[RIGHT_CAMERA][LEFT_BEACON] = 0;
    beaconAngle[RIGHT_CAMERA][RIGHT_BEACON] = 0;
}

void doBeaconAcquisition(int cLBeacon, int cRBeacon) {
    calculateCamera(LEFT_CAMERA, cLBeacon);
    calculateCamera(RIGHT_CAMERA, cRBeacon);
    seekBeacon(LEFT_CAMERA, cLBeacon);
    seekBeacon(RIGHT_CAMERA, cRBeacon);
    sendWiiData();
    //printf("\nLeft Camera Angle: %d\n", angleSet[LEFT_CAMERA]);
    //printf("Right Camera Angle: %d\n", angleSet[RIGHT_CAMERA]);
}

void doOverrideBeaconAcquisition(int cLBeacon, int cRBeacon) {
    if (!customBeaconCentered(cLBeacon, cRBeacon)) {
        doBeaconAcquisition(cLBeacon, cRBeacon);
    }
}

void doVerticalBeaconAcquisition() {
    doBeaconAcquisition(VERTICAL_BEACON, VERTICAL_BEACON);
}

void doHorizontalBeaconAcquisition() {
    doBeaconAcquisition(HORIZONTAL_BEACON, HORIZONTAL_BEACON);
}

void doContinuousAcquisition() {
    if (vertical) {
        if (!verticalBeaconCentered())
            //Look for the vertical Beacon
            doVerticalBeaconAcquisition();
        else
            vertical = false;
    } else {
        if (!horizontalBeaconCentered())
            //Look for the horizontal Beacon
            doHorizontalBeaconAcquisition();
        else
            vertical = true;
    }
}

void doXYAcquisition() {
    if (vertical) {
        if (!verticalBeaconCentered())
            //Look for the vertical Beacon
            doVerticalBeaconAcquisition();
        else
            vertical = false;
    } else {
        if (!horizontalBeaconCentered())
            //Look for the horizontal Beacon
            doHorizontalBeaconAcquisition();
        else {
            vertical = true;
            //Do Coordinate Data Acquisition
            struct coordinateData XY;
            if (calculateXY(&XY)) {
                printf("x: %f \n", XY.x);
                printf("y: %f \n", XY.y);
            }
        }
    }
}

int verticalBeaconCentered() {
    if (beaconCentered[LEFT_CAMERA][VERTICAL_BEACON] && beaconCentered[RIGHT_CAMERA][VERTICAL_BEACON]) {
        sendAngles(VERTICAL_BEACON, VERTICAL_BEACON);
        resetWiiBeaconStates();
        rotatingLeft[LEFT_CAMERA] = 0;
        rotatingLeft[RIGHT_CAMERA] = 0;
        return 1;
    } else return 0;
}

int horizontalBeaconCentered() {
    if (beaconCentered[LEFT_CAMERA][HORIZONTAL_BEACON] && beaconCentered[RIGHT_CAMERA][HORIZONTAL_BEACON]) {
        sendAngles(HORIZONTAL_BEACON, HORIZONTAL_BEACON);
        resetWiiBeaconStates();
        rotatingLeft[LEFT_CAMERA] = 1;
        rotatingLeft[RIGHT_CAMERA] = 1;
        return 1;
    } else return 0;
}

int customBeaconCentered(int left, int right) {
    if (beaconCentered[LEFT_CAMERA][left] && beaconCentered[RIGHT_CAMERA][right]) {
        sendAngles(left, right);
        resetWiiBeaconStates();
        rotatingLeft[LEFT_CAMERA] = 1;
        rotatingLeft[RIGHT_CAMERA] = 1;
        return 1;
    } else return 0;
}

bool calculateXY(struct coordinateData * returnable) {
    double c1, c2, d, e, f, H, V, h, g;

    struct WiiAngles angles;
    angles.cameraL_LeftBeacon = beaconAngle[LEFT_CAMERA][LEFT_BEACON];
    angles.cameraL_RightBeacon = beaconAngle[LEFT_CAMERA][RIGHT_BEACON];
    angles.cameraR_LeftBeacon = beaconAngle[RIGHT_CAMERA][LEFT_BEACON];
    angles.cameraR_RightBeacon = beaconAngle[RIGHT_CAMERA][RIGHT_BEACON];
    //Convert to radians from implied tenths degrees
    angles.cameraL_LeftBeacon *= (Pi / 1800.0);
    angles.cameraR_LeftBeacon *= (Pi / 1800.0);
    angles.cameraL_RightBeacon *= (Pi / 1800.0);
    angles.cameraL_RightBeacon *= (Pi / 1800.0);
    c1 = angles.cameraL_LeftBeacon - angles.cameraR_LeftBeacon;
    c2 = angles.cameraL_RightBeacon - angles.cameraL_RightBeacon;
    d = angles.cameraL_LeftBeacon - (c1 / 2.0);
    e = Pi - angles.cameraL_RightBeacon - (c2 / 2.0);
    f = Pi - d - e;

    H = (sin(Pi - angles.cameraL_LeftBeacon) * (physicalCameraWidth / 2.0)) / (sin(c1 / 2.0));
    H = fabs(H);

    V = (sin(angles.cameraL_RightBeacon) * (physicalCameraWidth / 2.0)) / (sin(c2 / 2.0));
    V = fabs(V);

    double temp = (V * sin(f)) / physicalBeaconWidth;
    h = asin(temp);
    g = Pi - h - f;

    printf("\na[0]: %f \n", angles.cameraL_LeftBeacon * (180.0 / Pi));
    printf("b[0]: %f \n", angles.cameraR_LeftBeacon * (180.0 / Pi));
    printf("c1: %f \n", c1 * (180.0 / Pi));
    printf("a[1]: %f \n", angles.cameraL_RightBeacon * (180.0 / Pi));
    printf("b[1]: %f \n", angles.cameraL_RightBeacon * (180.0 / Pi));
    printf("c2: %f \n", c2 * (180.0 / Pi));
    printf("d: %f \n", d * (180.0 / Pi));
    printf("e: %f \n", e * (180.0 / Pi));
    printf("f: %f \n", f * (180.0 / Pi));
    printf("g: %f \n", g * (180.0 / Pi));
    printf("Temp value for asin: %f \n", temp);
    printf("h: %f \n", h * (180.0 / Pi));
    printf("H: %f \n", H);
    printf("V: %f \n", V);

    if ((g > 1.5708) && (h < 1.5708)) {
        returnable->x = DistanceXFromWall - cos(Pi - g) * V;
        returnable->y = sin(Pi - g) * V;
        return true;
    } else if ((g < 1.5708) && (h < 1.5708)) {
        returnable->x = DistanceXFromWall + cos(g) * V;
        returnable->x = sin(g) * V;
        return true;
    } else if ((g < 1.5708) && (h > 1.5708)) {
        returnable->x = DistanceXFromWall + cos(g) * V;
        returnable->x = sin(g) * V;
        return true;
    } else if ((g == 1.5708)) {
        returnable->x = DistanceXFromWall;
        returnable->x = V;
        return true;
    } else if ((h == 1.5708)) {
        returnable->x = DistanceXFromWall + physicalBeaconWidth;
        returnable->x = H;
        return true;
    } else
        return false;

}

void debugBlobs(int cameraNumber) {
    WATCHDOG = cameraNumber;
    INDICATOR1 = OFF;
    INDICATOR2 = OFF;
    INDICATOR3 = OFF;
    INDICATOR4 = OFF;
    if (Camera[cameraNumber].result & BLOB1) {
        INDICATOR1 = ON;
    }
    if (Camera[cameraNumber].result & BLOB2) {
        INDICATOR2 = ON;
    }
    if (Camera[cameraNumber].result & BLOB3) {
        INDICATOR3 = ON;
    }
    if (Camera[cameraNumber].result & BLOB4) {
        INDICATOR4 = ON;
    }

    delay(500);
    INDICATOR1 = OFF;
    INDICATOR2 = OFF;
    INDICATOR3 = OFF;
    INDICATOR4 = OFF;
    WATCHDOG = OFF;
    delay(500);
}

void sendWiiData(int beaconLeft, int beaconRight) {
    ToSend(WII_BEACON_SEEN_LEFT, beaconSeen[LEFT_CAMERA]);
    ToSend(WII_BEACON_SEEN_RIGHT, beaconSeen[RIGHT_CAMERA]);
    ToSend(WII_NUMBER_SWEEPS_SINCE_MOVE, numberSweeps[0]);
    ToSend(WII_LEFT_CAMERA_ANGLE, angleSet[LEFT_CAMERA]);
    ToSend(WII_RIGHT_CAMERA_ANGLE, angleSet[RIGHT_CAMERA]);
    ToSend(WII_LEFT_CAMERA_LOCKED, beaconCentered[LEFT_CAMERA][beaconLeft]);
    ToSend(WII_RIGHT_CAMERA_LOCKED, beaconCentered[RIGHT_CAMERA][beaconRight]);
    sendData(NAVIGATION_ADDRESS);
    delay(5);
    ToSend(WII_CAMERA_LEFT_ANGLE, angleSet[LEFT_CAMERA]/10.0);
    ToSend(WII_CAMERA_RIGHT_ANGLE, angleSet[RIGHT_CAMERA]/10.0);
    ToSend(WII_CAMERA_LEFT_LOCKED, beaconCentered[LEFT_CAMERA][beaconLeft]);
    ToSend(WII_CAMERA_RIGHT_LOCKED, beaconCentered[RIGHT_CAMERA][beaconRight]);
    sendData(CONTROL_ADDRESS);
    delay(5);

}

void sendAngles(int beaconLeft, int beaconRight) {
    ToSend(WII_LEFT_CAMERA_ANGLE, beaconAngle[LEFT_CAMERA][beaconLeft]);
    ToSend(WII_RIGHT_CAMERA_ANGLE, beaconAngle[RIGHT_CAMERA][beaconRight]);
    ToSend(WII_LEFT_CAMERA_LOCKED, beaconCentered[LEFT_CAMERA][beaconLeft]);
    ToSend(WII_RIGHT_CAMERA_LOCKED, beaconCentered[RIGHT_CAMERA][beaconRight]);
    sendData(NAVIGATION_ADDRESS);
    delay(5);
    ToSend(WII_CAMERA_LEFT_ANGLE, angleSet[LEFT_CAMERA]);
    ToSend(WII_CAMERA_RIGHT_ANGLE, angleSet[RIGHT_CAMERA]);
    ToSend(WII_CAMERA_LEFT_LOCKED, beaconCentered[LEFT_CAMERA][beaconLeft]);
    ToSend(WII_CAMERA_RIGHT_LOCKED, beaconCentered[RIGHT_CAMERA][beaconRight]);
    sendData(CONTROL_ADDRESS);
    delay(5);
}

void calculateCamera(int cameraNumber, int beaconNumber) {

    int minHeight = 999;
    int minWidth = 999;

    Camera[cameraNumber].result = read(cameraNumber);
    //debugBlobs(cameraNumber);

    //Clear the center blob marker before continuing
    centerBlob[beaconNumber][cameraNumber] = INVALID;

    if ((Camera[cameraNumber].result & BLOB1) && (Camera[cameraNumber].result & BLOB2)) {
        if (isAbout(Camera[cameraNumber].Blob1.Y, Camera[cameraNumber].Blob2.Y, HEIGH_WIDTH_COMPARE))
            if (abs((Camera[cameraNumber].Blob1.Y - Camera[cameraNumber].Blob2.Y)) < minHeight) {
                centerBlob[HORIZONTAL_BEACON][cameraNumber] = (Camera[cameraNumber].Blob1.X + Camera[cameraNumber].Blob2.X) / 2;
                minHeight = centerBlob[HORIZONTAL_BEACON][cameraNumber];
            }
        if (isAbout(Camera[cameraNumber].Blob1.X, Camera[cameraNumber].Blob2.X, HEIGH_WIDTH_COMPARE))
            if (abs((Camera[cameraNumber].Blob1.X - Camera[cameraNumber].Blob2.X)) < minWidth) {
                centerBlob[VERTICAL_BEACON][cameraNumber] = (Camera[cameraNumber].Blob1.X + Camera[cameraNumber].Blob2.X) / 2;
                minWidth = centerBlob[VERTICAL_BEACON][cameraNumber];
            }
    }
    if ((Camera[cameraNumber].result & BLOB1) && (Camera[cameraNumber].result & BLOB3)) {
        if (isAbout(Camera[cameraNumber].Blob1.Y, Camera[cameraNumber].Blob3.Y, HEIGH_WIDTH_COMPARE))
            if (abs((Camera[cameraNumber].Blob1.Y - Camera[cameraNumber].Blob3.Y)) < minHeight) {
                centerBlob[HORIZONTAL_BEACON][cameraNumber] = (Camera[cameraNumber].Blob1.X + Camera[cameraNumber].Blob3.X) / 2;
                minHeight = centerBlob[HORIZONTAL_BEACON][cameraNumber];
            }
        if (isAbout(Camera[cameraNumber].Blob1.X, Camera[cameraNumber].Blob3.X, HEIGH_WIDTH_COMPARE))
            if (abs((Camera[cameraNumber].Blob1.X - Camera[cameraNumber].Blob3.X)) < minWidth) {
                centerBlob[VERTICAL_BEACON][cameraNumber] = (Camera[cameraNumber].Blob1.X + Camera[cameraNumber].Blob3.X) / 2;
                minWidth = centerBlob[VERTICAL_BEACON][cameraNumber];
            }
    }
    if ((Camera[cameraNumber].result & BLOB1) && (Camera[cameraNumber].result & BLOB4)) {
        if (isAbout(Camera[cameraNumber].Blob1.Y, Camera[cameraNumber].Blob4.Y, HEIGH_WIDTH_COMPARE))
            if (abs((Camera[cameraNumber].Blob1.Y - Camera[cameraNumber].Blob4.Y)) < minHeight) {
                centerBlob[HORIZONTAL_BEACON][cameraNumber] = (Camera[cameraNumber].Blob1.X + Camera[cameraNumber].Blob4.X) / 2;
                minHeight = centerBlob[HORIZONTAL_BEACON][cameraNumber];
            }
        if (isAbout(Camera[cameraNumber].Blob1.X, Camera[cameraNumber].Blob4.X, HEIGH_WIDTH_COMPARE))
            if (abs((Camera[cameraNumber].Blob1.X - Camera[cameraNumber].Blob4.X)) < minWidth) {
                centerBlob[VERTICAL_BEACON][cameraNumber] = (Camera[cameraNumber].Blob1.X + Camera[cameraNumber].Blob4.X) / 2;
                minWidth = centerBlob[VERTICAL_BEACON][cameraNumber];
            }
    }
    if ((Camera[cameraNumber].result & BLOB2) && (Camera[cameraNumber].result & BLOB3)) {
        if (isAbout(Camera[cameraNumber].Blob2.Y, Camera[cameraNumber].Blob3.Y, HEIGH_WIDTH_COMPARE))
            if (abs((Camera[cameraNumber].Blob2.Y - Camera[cameraNumber].Blob3.Y)) < minHeight) {
                centerBlob[HORIZONTAL_BEACON][cameraNumber] = (Camera[cameraNumber].Blob2.X + Camera[cameraNumber].Blob3.X) / 2;
                minHeight = centerBlob[HORIZONTAL_BEACON][cameraNumber];
            }
        if (isAbout(Camera[cameraNumber].Blob2.X, Camera[cameraNumber].Blob3.X, HEIGH_WIDTH_COMPARE))
            if (abs((Camera[cameraNumber].Blob2.X - Camera[cameraNumber].Blob3.X)) < minWidth) {
                centerBlob[VERTICAL_BEACON][cameraNumber] = (Camera[cameraNumber].Blob2.X + Camera[cameraNumber].Blob3.X) / 2;
                minWidth = centerBlob[VERTICAL_BEACON][cameraNumber];
            }
    }
    if ((Camera[cameraNumber].result & BLOB2) && (Camera[cameraNumber].result & BLOB4)) {
        if (isAbout(Camera[cameraNumber].Blob2.Y, Camera[cameraNumber].Blob4.Y, HEIGH_WIDTH_COMPARE))
            if (abs((Camera[cameraNumber].Blob2.Y - Camera[cameraNumber].Blob4.Y)) < minHeight) {
                centerBlob[HORIZONTAL_BEACON][cameraNumber] = (Camera[cameraNumber].Blob2.X + Camera[cameraNumber].Blob4.X) / 2;
                minHeight = centerBlob[HORIZONTAL_BEACON][cameraNumber];
            }
        if (isAbout(Camera[cameraNumber].Blob2.X, Camera[cameraNumber].Blob4.X, HEIGH_WIDTH_COMPARE))
            if (abs((Camera[cameraNumber].Blob2.X - Camera[cameraNumber].Blob4.X)) < minWidth) {
                centerBlob[VERTICAL_BEACON][cameraNumber] = (Camera[cameraNumber].Blob2.X + Camera[cameraNumber].Blob4.X) / 2;
                minWidth = centerBlob[VERTICAL_BEACON][cameraNumber];
            }
    }
    if ((Camera[cameraNumber].result & BLOB3) && (Camera[cameraNumber].result & BLOB4)) {
        if (isAbout(Camera[cameraNumber].Blob3.Y, Camera[cameraNumber].Blob4.Y, HEIGH_WIDTH_COMPARE))
            if (abs((Camera[cameraNumber].Blob3.Y - Camera[cameraNumber].Blob4.Y)) < minHeight) {
                centerBlob[HORIZONTAL_BEACON][cameraNumber] = (Camera[cameraNumber].Blob3.X + Camera[cameraNumber].Blob4.X) / 2;
                minHeight = centerBlob[HORIZONTAL_BEACON][cameraNumber];
            }
        if (isAbout(Camera[cameraNumber].Blob3.X, Camera[cameraNumber].Blob4.X, HEIGH_WIDTH_COMPARE))
            if (abs((Camera[cameraNumber].Blob3.X - Camera[cameraNumber].Blob4.X)) < minWidth) {
                centerBlob[VERTICAL_BEACON][cameraNumber] = (Camera[cameraNumber].Blob3.X + Camera[cameraNumber].Blob4.X) / 2;
                minWidth = centerBlob[VERTICAL_BEACON][cameraNumber];
            }
    }
}

int isAbout(int compareThis, int toThis, int range) {
    return ((compareThis > toThis - range) && (compareThis < toThis + range));
}

void seekBeacon(int cameraNumber, int beaconNumber) {

    //centerBlob[beaconNumber][cameraNumber] = INVALID;
    if (centerBlob[beaconNumber][cameraNumber] == INVALID) {
        beaconSeen[cameraNumber] = 0;
        beaconCentered[cameraNumber][beaconNumber] = 0;
        if ((angleSet[cameraNumber] < SERVO_MAX - (1.5*SERVO_STEP_WIDE)) && !rotatingLeft[cameraNumber]) {
            angleSet[cameraNumber] += SERVO_STEP_WIDE;
            if (cameraNumber == 0) setAngle1(angleSet[cameraNumber]);
            else setAngle2(angleSet[cameraNumber]);
        } else {
            rotatingLeft[cameraNumber] = 1;
            numberSweeps[cameraNumber]++;
        }

        if ((angleSet[cameraNumber] > SERVO_MIN + (1.5*SERVO_STEP_WIDE)) && rotatingLeft[cameraNumber]) {
            angleSet[cameraNumber] -= SERVO_STEP_WIDE;
            if (cameraNumber == 0) setAngle1(angleSet[cameraNumber]);
            else setAngle2(angleSet[cameraNumber]);
        } else {
            rotatingLeft[cameraNumber] = 0;
            numberSweeps[cameraNumber]++;
        }
    } else {
        if (cameraNumber == LEFT_CAMERA) {
            if (!isAbout(centerBlob[beaconNumber][cameraNumber], CENTER_PIXEL_LEFT, ACCEPTABLE_CENTER_WIDTH)) {
                beaconSeen[cameraNumber] = 1;
                beaconCentered[cameraNumber][beaconNumber] = 0;
                if (centerBlob[beaconNumber][cameraNumber] > CENTER_PIXEL_LEFT) {
                    if (angleSet[cameraNumber] > (SERVO_MIN+DEADZONE))
                    angleSet[cameraNumber] -= ((centerBlob[beaconNumber][cameraNumber] - CENTER_PIXEL_LEFT)) / 5;
                    if (cameraNumber == 0) setAngle1(angleSet[cameraNumber]);
                    else setAngle2(angleSet[cameraNumber]);
                } else {

                    if (angleSet[cameraNumber] < (SERVO_MAX-DEADZONE))
                    angleSet[cameraNumber] += ((CENTER_PIXEL_LEFT - centerBlob[beaconNumber][cameraNumber])) / 5;
                    if (cameraNumber == 0) setAngle1(angleSet[cameraNumber]);
                    else setAngle2(angleSet[cameraNumber]);
                }
            } else {
                beaconAngle[beaconNumber][cameraNumber] = angleSet[cameraNumber];
                beaconCentered[cameraNumber][beaconNumber] = 1;
            }
        } else {
            if (!isAbout(centerBlob[beaconNumber][cameraNumber], CENTER_PIXEL_RIGHT, ACCEPTABLE_CENTER_WIDTH)) {
                beaconSeen[cameraNumber] = 1;
                beaconCentered[cameraNumber][beaconNumber] = 0;
                if (centerBlob[beaconNumber][cameraNumber] > CENTER_PIXEL_RIGHT) {
                    if (angleSet[cameraNumber] > (SERVO_MIN+DEADZONE))
                    angleSet[cameraNumber] -= ((centerBlob[beaconNumber][cameraNumber] - CENTER_PIXEL_RIGHT)) / 5;
                    if (cameraNumber == 0) setAngle1(angleSet[cameraNumber]);
                    else setAngle2(angleSet[cameraNumber]);
                } else {
                    if (angleSet[cameraNumber] < (SERVO_MAX-DEADZONE))
                    angleSet[cameraNumber] += ((CENTER_PIXEL_RIGHT - centerBlob[beaconNumber][cameraNumber])) / 5;
                    if (cameraNumber == 0) setAngle1(angleSet[cameraNumber]);
                    else setAngle2(angleSet[cameraNumber]);
                }
            } else {
                beaconAngle[beaconNumber][cameraNumber] = angleSet[cameraNumber];
                beaconCentered[cameraNumber][beaconNumber] = 1;
            }
        }
    }
}


void delay(int ms) {
    time = 0;
    while (time < ms);
}

void initCamera(int cameraNumber) {
    unsigned char data[2];
    data[0] = 0x30;
    data[1] = 0x01;
    if (cameraNumber == 0) {
        SendI2Cone(camera, data, 2);
        while (StatusI2Cone() == 0);
    } else {
        SendI2Ctwo(camera, data, 2);
        while (StatusI2Ctwo() == 0);
    }

    data[0] = 0x30;
    data[1] = 0x08;
    if (cameraNumber == 0) {
        SendI2Cone(camera, data, 2);
        while (StatusI2Cone() == 0);
    } else {
        SendI2Ctwo(camera, data, 2);
        while (StatusI2Ctwo() == 0);
    }

    data[0] = 0x06;
    data[1] = 0x90;
    if (cameraNumber == 0) {
        SendI2Cone(camera, data, 2);
        while (StatusI2Cone() == 0);
    } else {
        SendI2Ctwo(camera, data, 2);
        while (StatusI2Ctwo() == 0);
    }

    data[0] = 0x08;
    data[1] = 0xC0;
    if (cameraNumber == 0) {
        SendI2Cone(camera, data, 2);
        while (StatusI2Cone() == 0);
    } else {
        SendI2Ctwo(camera, data, 2);
        while (StatusI2Ctwo() == 0);
    }

    data[0] = 0x1A;
    data[1] = 0x40;
    if (cameraNumber == 0) {
        SendI2Cone(camera, data, 2);
        while (StatusI2Cone() == 0);
    } else {
        SendI2Ctwo(camera, data, 2);
        while (StatusI2Ctwo() == 0);
    }

    data[0] = 0x33;
    data[1] = 0x33;
    if (cameraNumber == 0) {
        SendI2Cone(camera, data, 2);
        while (StatusI2Cone() == 0);
    } else {
        SendI2Ctwo(camera, data, 2);
        while (StatusI2Ctwo() == 0);
    }

}
void readCamera(int cameraNumber){
    if (cameraNumber == LEFT_CAMERA) {
        ReceiveI2Cone(camera, data_address, Camera[LEFT_CAMERA].data_buf, 16);

    } else {
        ReceiveI2Ctwo(camera, data_address, Camera[RIGHT_CAMERA].data_buf, 16);
    }
}
int cameraReady(int cameraNumber)
{
    int returnable;
    if (cameraNumber == 1) {
        returnable = StatusI2Ctwo();

    } else {
        returnable = StatusI2Cone();
    }
    return returnable;
}
unsigned char read(int cameraNumber) {


    int s;
    unsigned char blobcount = 0;

    Camera[cameraNumber].Blob1.X = Camera[cameraNumber].data_buf[1];
    Camera[cameraNumber].Blob1.Y = Camera[cameraNumber].data_buf[2];
    s = Camera[cameraNumber].data_buf[3];
    Camera[cameraNumber].Blob1.X += (s & 0x30) << 4;
    Camera[cameraNumber].Blob1.Y += (s & 0xC0) << 2;
    Camera[cameraNumber].Blob1.Size = (s & 0x0F);

    // At the moment we're using the size of the blob to determine if one is detected, either X,Y, or size could be used.
    blobcount |= (Camera[cameraNumber].Blob1.Size < 15) ? BLOB1 : 0;

    Camera[cameraNumber].Blob2.X = Camera[cameraNumber].data_buf[4];
    Camera[cameraNumber].Blob2.Y = Camera[cameraNumber].data_buf[5];
    s = Camera[cameraNumber].data_buf[6];
    Camera[cameraNumber].Blob2.X += (s & 0x30) << 4;
    Camera[cameraNumber].Blob2.Y += (s & 0xC0) << 2;
    Camera[cameraNumber].Blob2.Size = (s & 0x0F);

    blobcount |= (Camera[cameraNumber].Blob2.Size < 15) ? BLOB2 : 0;

    Camera[cameraNumber].Blob3.X = Camera[cameraNumber].data_buf[7];
    Camera[cameraNumber].Blob3.Y = Camera[cameraNumber].data_buf[8];
    s = Camera[cameraNumber].data_buf[9];
    Camera[cameraNumber].Blob3.X += (s & 0x30) << 4;
    Camera[cameraNumber].Blob3.Y += (s & 0xC0) << 2;
    Camera[cameraNumber].Blob3.Size = (s & 0x0F);

    blobcount |= (Camera[cameraNumber].Blob3.Size < 15) ? BLOB3 : 0;

    Camera[cameraNumber].Blob4.X = Camera[cameraNumber].data_buf[10];
    Camera[cameraNumber].Blob4.Y = Camera[cameraNumber].data_buf[11];
    s = Camera[cameraNumber].data_buf[12];
    Camera[cameraNumber].Blob4.X += (s & 0x30) << 4;
    Camera[cameraNumber].Blob4.Y += (s & 0xC0) << 2;
    Camera[cameraNumber].Blob4.Size = (s & 0x0F);

    blobcount |= (Camera[cameraNumber].Blob4.Size < 15) ? BLOB4 : 0;
    return blobcount;
}
