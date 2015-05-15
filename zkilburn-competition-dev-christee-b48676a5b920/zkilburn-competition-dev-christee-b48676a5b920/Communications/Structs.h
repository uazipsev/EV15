//structs.h

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
//------------------------COMM structs---------------------------

// data from control to robot
//struct fromContoltoComm
//{
//  int leftMotorSpeed;
//  int rightMotorSpeed;
//  uint8_t actuator;
//  uint8_t macro_command;
//  int macro_sub_command;
//  uint8_t macro_stop;
//}
//fromControl;

//struct toNavfromComm {
//  uint8_t macro_command;
//  uint8_t macro_sub_command;
//  bool macro_stop;
//  int leftMotorSpeed;
//  int rightMotorSpeed;
//  uint8_t actuator;
//}
//toNav;
//
//struct fromNavtoComm {
//  int8_t lM;
//  int8_t rM;
//  bool macro_complete;
//  uint8_t macro_command;
//  uint8_t macro_sub_command;
//  bool macro_active;
//  int LongFront;
//  int LongLeft;
//  int LongRight;
//  int LongBack;
//  int ShortLeft;
//  int ShortRight;
//  int volts;
//  int amps;
//  int amphour;
//  float encoderR;
//  float encoderL;
//  unsigned int encoderSpeedR;
//  unsigned int encoderSpeedL;
//  float gyro;
//}
//fromNav;


//struct fromCommtoControl
//{
//  uint8_t macro_command;
//  bool macro_complete;
//  int8_t motorL;
//  int8_t motorR;
//  int LongFront;
//  int LongLeft;
//  int LongRight;
//  int LongBack;
//  int ShortLeft;
//  int ShortRight;
//  int volts;
//  int amps;
//  int amphour;
//  float encoderR;
//  float encoderL;
//  unsigned int encoderSpeedR;
//  unsigned int encoderSpeedL;
//  float gyro;
//}
//toControl;




struct ledControl {
  uint8_t state;
  uint16_t color;
}
led;







