
#include "MPU.h"

MPU::MPU(word address)
{
  MPUaddress=address; 
}

void MPU::MPUinit()
{
  // Clear the 'sleep' bit to start the sensor.
  MPU6050_write_reg(MPU6050_PWR_MGMT_1, 0); 
  MPU6050_write_reg(MPU6050_CONFIG,MPU6050_CONFIG_DLPF);
  MPU6050_write_reg(MPU6050_SAMPLE_RATE,49);  
  //Set Gyro Sensativity
  MPU6050_write_reg(MPU6050_GYRO_CONFIG, MPU6050_FS_SEL_3); //+-2000deg/sec (/16.4)
  MPU6050_write_reg(MPU6050_ACCEL_CONFIG, MPU6050_FS_SEL_3); //+-16g (/4095)

}
int MPU::readGyroZ()
{

  return 1;
}
int MPU::readGyroY()
{
  MPU6050_read (MPU6050_GYRO_YOUT_H, (uint8_t *) &Gyrostorage, sizeof(Gyrostorage)); 

  SWAP (Gyrostorage.reg.y_gyro_h, Gyrostorage.reg.y_gyro_l);

  _yGyro=Gyrostorage.value.y_gyro;
  return 1;

}
int MPU::readGyroX()
{

  return 1;

}
int MPU::readAccelX()
{

  return 1;

}
int MPU::readAccelY()
{

  return 1;

}
int MPU::readAccelZ()
{

  return 1;

}

void MPU::readAll()
{ 
  MPU6050_read (MPU6050_ACCEL_XOUT_H, (uint8_t *) &MPUstorage, sizeof(MPUstorage)); 


  SWAP (MPUstorage.reg.x_accel_h, MPUstorage.reg.x_accel_l);
  SWAP (MPUstorage.reg.y_accel_h, MPUstorage.reg.y_accel_l);
  SWAP (MPUstorage.reg.z_accel_h, MPUstorage.reg.z_accel_l);
  SWAP (MPUstorage.reg.t_h, MPUstorage.reg.t_l);
  SWAP (MPUstorage.reg.x_gyro_h, MPUstorage.reg.x_gyro_l);
  SWAP (MPUstorage.reg.y_gyro_h, MPUstorage.reg.y_gyro_l);
  SWAP (MPUstorage.reg.z_gyro_h, MPUstorage.reg.z_gyro_l);


  _xAccel=MPUstorage.value.x_accel;
  _yAccel=MPUstorage.value.y_accel;
  _zAccel=MPUstorage.value.z_accel;
  _xGyro=MPUstorage.value.x_gyro;
  _yGyro=MPUstorage.value.y_gyro;
  _zGyro=MPUstorage.value.z_gyro;
  return;
}

// --------------------------------------------------------
// MPU6050_read
int MPU::MPU6050_read(int starts, uint8_t *buffer, uint8_t sized)
{
  int i, n, error;

  Wire.beginTransmission(MPUaddress);
  n = Wire.write(starts);
  if (n != 1)
    return (-10);

  n = Wire.endTransmission(false);    // hold the I2C-bus
  if (n != 0)
    return (n);

  // Third parameter is true: relase I2C-bus after data is read.
  Wire.requestFrom(MPUaddress, sized, (uint8_t) true);
  i = 0;
  while (Wire.available() && i < sized)
  {
    buffer[i++] = Wire.read();
  }
  if ( i != sized)
    return (-11);

  return (0);  // return : no error
}

// --------------------------------------------------------
// MPU6050_write
int MPU::MPU6050_write(int starts, const uint8_t *pData,  uint8_t sized)
{
  int n, error;
  Wire.beginTransmission(MPUaddress);
  n = Wire.write(starts);        // write the start address
  if (n != 1)
    return (-20);

  n = Wire.write(pData, sized);  // write data bytes
  if (n != sized)
    return (-21);

  error = Wire.endTransmission(true); // release the I2C-bus
  if (error != 0)
    return (error);
  return (0);         // return : no error
}

// --------------------------------------------------------
// MPU6050_write_reg
int MPU::MPU6050_write_reg(int reg, uint8_t data)
{
  int error;
  error = MPU6050_write(reg, &data, 1);
  return (error);
}


