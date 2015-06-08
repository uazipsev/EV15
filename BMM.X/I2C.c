#include <xc.h>
#include <stdbool.h>
#include "I2C.h"
#include <i2c.h>

void i2c_wait(unsigned int cnt) {
    while (--cnt) {
        asm( "nop");
        asm( "nop");
    }
}

void i2c_Write(char address, bool read_write, char *data, int numofbytes) {
    char i2cData[10];
    int DataSz;
    int Index = 0;
    unsigned char *pWrite = 0;
    char status;
    DataSz = numofbytes;

    StartI2C1(); //Send the Start Bit
    IdleI2C1(); //Wait to complete
    if (read_write == 1) //write address
    {
        MasterWriteI2C1(((address << 1) | 0));
        IdleI2C1(); //Wait to complete
    } else //read address
    {
        MasterWriteI2C1(((address << 1) | 1));
        IdleI2C1(); //Wait to complete
    }

    while (DataSz) {
        MasterWriteI2C1(data[Index++]);
        IdleI2C1(); //Wait to complete

        DataSz--;

        //ACKSTAT is 0 when slave acknowledge,
        //if 1 then slave has not acknowledge the data.
        if (I2C1STATbits.ACKSTAT)
            break;
    }
    status = MasterputsI2C1(pWrite);

    if (status == -3)
        while (1);

    StopI2C1(); //Send the Stop condition
    IdleI2C1(); //Wait to complete

    // wait for eeprom to complete write process. poll the ack status
    while (1) {
        i2c_wait(10);

        StartI2C1(); //Send the Start Bit
        IdleI2C1(); //Wait to complete

        MasterWriteI2C1(i2cData[0]);
        IdleI2C1(); //Wait to complete

        if (I2C1STATbits.ACKSTAT == 0) //eeprom has acknowledged
        {
            StopI2C1(); //Send the Stop condition
            IdleI2C1(); //Wait to complete
            break;
        }

        StopI2C1(); //Send the Stop condition
        IdleI2C1(); //Wait to complete
    }
}

void i2c_init(void) {
    I2C1BRG = 0x0258;
    I2C1CON = 0x1200;
    I2C1RCV = 0x0000;
    I2C1TRN = 0x0000;
    //Now we can enable the peripheral
    I2C1CON = 0x9200;
}