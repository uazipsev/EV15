#include "MCP4725.h"
#include "I2C.h"
#include "PinDef.h"

// Datasheet: http://ww1.microchip.com/downloads/en/DeviceDoc/22039d.pdf

char i2cdata[20];


void SetDAC1(long int value)
{
    i2cdata[0] = value >> 8;
    i2cdata[1] = value & 0x00ff;
    i2c_Write(DAC1Address, true, i2cdata, 2);
}


void SetDAC2(long int value)
{
    i2cdata[0] = value >> 8;
    i2cdata[1] = value & 0x00ff;
    i2c_Write(DAC2Address, true, i2cdata, 2);
}

//NOTE: this fcn needs revised. see pg 25 of Data sheet
void ConfigDAC(char address,long int setpoint)
{
    i2cdata[0] = setpoint >> 8;
    i2cdata[1] = setpoint & 0x00ff;
    i2cdata[0] = i2cdata[0] | 0x70;  //program mode
    i2c_Write(address, true, i2cdata, 2);
}