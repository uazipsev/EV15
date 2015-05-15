#define COMMAquire 0
#define AUTO 1
#define MACRO 2
#define MANUAL 3
#define CHRISTMAS 4
#define PARTY 5
#define OVERRIDE 6
#define ERRORED 7

#define DEBUGcomm 0
#define WDTcomm 1
#define LEDcomm 2
#define PICcomm 3
#define commSelect0 23
#define commSelect1 22

//---------------------------------MASTER DEFINE LIST--------------------------------------
//IR tolerance
#define updateRange 45


#define RIGHTLONG 1
#define LEFTLONG 2
#define BACKLONG 0
#define FRONTLONG 3
//------------------------MACRO Definitions---------------------------
//macro state definitions
#define TURN 1
#define DRIVE 2
#define ACTUATOR 3

//commands
#define Lside false
#define Rside true

//turning tuning
#define LEFT 1
#define RIGHT 2

#define L1 1
#define L2 2
#define L3 3
#define L4 4
#define L5 5
#define L6 6
#define R1 7
#define R2 8
#define R3 9
#define R4 10
#define R5 11
#define R6 12
//------------------------Gyroscope Definitions---------------------------
#define SWAP(x,y) swap = x; x = y; y = swap
// define the gyro i2c port
#define MPU6050_I2C_ADDRESS 0x68//69
//Bit definitions
#define MPU6050_D0 0
#define MPU6050_D1 1
#define MPU6050_D2 2
#define MPU6050_D3 3
#define MPU6050_D4 4
#define MPU6050_D5 5
#define MPU6050_D6 6
#define MPU6050_D7 7
//important registers (from source code)
#define MPU6050_PWR_MGMT_1         0x6B   // R/W
#define MPU6050_PWR_MGMT_2         0x6C   // R/W
#define MPU6050_GYRO_CONFIG        0x1B   // R/W
#define MPU6050_ACCEL_CONFIG       0x1C   // R/W
#define MPU6050_ACCEL_XOUT_H       0x3B   // R  
#define MPU6050_ACCEL_XOUT_L       0x3C   // R  
#define MPU6050_ACCEL_YOUT_H       0x3D   // R  
#define MPU6050_ACCEL_YOUT_L       0x3E   // R  
#define MPU6050_ACCEL_ZOUT_H       0x3F   // R  
#define MPU6050_ACCEL_ZOUT_L       0x40   // R  
#define MPU6050_TEMP_OUT_H         0x41   // R  
#define MPU6050_TEMP_OUT_L         0x42   // R  
#define MPU6050_GYRO_XOUT_H        0x43   // R  
#define MPU6050_GYRO_XOUT_L        0x44   // R  
#define MPU6050_GYRO_YOUT_H        0x45   // R  
#define MPU6050_GYRO_YOUT_L        0x46   // R  
#define MPU6050_GYRO_ZOUT_H        0x47   // R  
#define MPU6050_GYRO_ZOUT_L        0x48   // R  
#define MPU6050_FS_SEL0 MPU6050_D3
#define MPU6050_FS_SEL1 MPU6050_D4
// Combined definitions for the FS_SEL values
#define MPU6050_FS_SEL_0 (0)
#define MPU6050_FS_SEL_1 (bit(MPU6050_FS_SEL0))
#define MPU6050_FS_SEL_2 (bit(MPU6050_FS_SEL1))
#define MPU6050_FS_SEL_3 (bit(MPU6050_FS_SEL1)|bit(MPU6050_FS_SEL0))

//------------------------LED Definitions---------------------------
#define RED 0
#define BLUE 1
#define GREEN 2
#define TEAL 3
#define YELLOW 4
//------------------------Autonomous Definitions---------------------------
#define start 1
#define digSite 2
#define backward 1
#define forward 0

//temporary location start
#define startLocationX 9//97
#define startLocationY 7//75

//locations of important stuff
#define startCenterX 19//194
#define startCenterY 7//75
#define digSiteCenterX 19//194
#define digSiteCenterY 20//600
#define dumpSiteX 19//194
#define dumpSiteY 2//20

//noted witdth and length base
#define robotWidth 74
#define robotLength 100

//AUTO directions
#define XPOSITIVE 0
#define YPOSITIVE 90
#define XNEGATIVE 180
#define YNEGATIVE 270

//------------------------Sensor Definitions---------------------------
//Define all analog output pins (supposed to be attached to distribution board)
#define ANALOG0 A0  //J1 - Front Long
#define ANALOG1 A1  //J6  -BL Stereo
#define ANALOG2 A2
#define ANALOG3 A3
#define ANALOG4 A4  //J24  ACTUATOR
#define ANALOG5 A5  //J25  Rear Long
#define ANALOG6 A6  //J27  Left Long
#define ANALOG7 A7  //J28  Right Long
#define ANALOG8 A8
#define ANALOG9 A9
#define ANALOG10 A10
#define ANALOG11 A11
#define ANALOG12 A12
#define ANALOG13 A13
#define ANALOG14 A14
#define ANALOG15 A15

//Define all digital output pins (supposed to be attached to distribution board)
#define DIGITAL1 22
#define DIGITAL2 23
#define DIGITAL3 24
#define DIGITAL4 25
#define DIGITAL5 26
#define DIGITAL6 27
#define DIGITAL7 28
#define DIGITAL8 29
#define DIGITAL9 37
#define DIGITAL10 36
#define DIGITAL11 35
#define DIGITAL12 34
#define DIGITAL13 33
#define DIGITAL14 32
#define DIGITAL15 31
#define DIGITAL16 30


#define ACTUATORP ANALOG4
#define VIBRATOR 8




