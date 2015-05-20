#include "MCP4725.h"
#include "I2C_API.h"
#include "PinDef.h"

char i2cdata[20];

void SetDAC1(long int value)
{
    i2cdata[0] = 1;
    i2cdata[1] = 1;
    i2c_Write(0x60, true, i2cdata, 2);
}

void SetDAC2(long int value)
{
    i2cdata[0] = 1;
    i2cdata[1] = 1;
    i2c_Write(0x61, true, i2cdata, 2);
}
