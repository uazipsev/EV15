//Structs.h
struct driveData
{
  int leftMotorSpeed;
  int rightMotorSpeed;
} 
inputData;

//Gyro Struc
typedef union gyro_union
{
  struct
  {
    uint8_t z_gyro_h;
    uint8_t z_gyro_l;
  }
  reg;
  struct
  {
    int16_t z_gyro;
  }
  value;
};
gyro_union gyro;





