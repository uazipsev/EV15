#ifndef MPU_h
#define MPU_h

#include "Arduino.h"
#include<Wire.h>
#define DEBUG_CALIBRATE false

#define SWAP(x,y) swap = x; x = y; y = swap

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
#define MPU6050_CONFIG             0x1A   // R/W
#define MPU6050_SAMPLE_RATE        0x19   // R/W
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
#define MPU6050_CONFIG_DLPF 1

class MPU
{
public:
  MPU(word address);
  void MPUinit();
  uint8_t MPUaddress;

  int _xAccel, _yAccel, _zAccel, _xGyro, _yGyro, _zGyro;

  void readAll();
  int readGyroZ();
  int readGyroY();
  int readGyroX();
  int readAccelX();
  int readAccelY();
  int readAccelZ();

private:


  //Gyro Struct
  typedef union gyro_accel_union
  {
    struct
    {
      uint8_t x_accel_h;
      uint8_t x_accel_l;
      uint8_t y_accel_h;
      uint8_t y_accel_l;
      uint8_t z_accel_h;
      uint8_t z_accel_l;
      uint8_t t_h;
      uint8_t t_l;
      uint8_t x_gyro_h;
      uint8_t x_gyro_l;
      uint8_t y_gyro_h;
      uint8_t y_gyro_l;
      uint8_t z_gyro_h;
      uint8_t z_gyro_l;
    }
    reg;
    struct
    {
      int16_t x_accel;
      int16_t y_accel;
      int16_t z_accel;
      int16_t temperature;
      int16_t x_gyro;
      int16_t y_gyro;
      int16_t z_gyro;
    }
    value;
  };
  gyro_accel_union MPUstorage;

  typedef union gyro_union
  {
    struct
    {
      uint8_t y_gyro_h;
      uint8_t y_gyro_l;
    }
    reg;
    struct
    {
      int16_t y_gyro;
    }
    value;
  };
  gyro_union Gyrostorage;

  int8_t swap;
  int MPU6050_read(int starts, uint8_t *buffer,  uint8_t sized);
  int MPU6050_write(int starts, const uint8_t *pData,  uint8_t sized);
  int MPU6050_write_reg(int reg, uint8_t data);

};


#endif




