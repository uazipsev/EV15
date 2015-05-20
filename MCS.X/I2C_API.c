#include <xc.h>
#include <stdbool.h>
#include "I2C_API.h"
#include <i2c.h>

void i2c_wait(unsigned int cnt)
{
	while(--cnt)
	{
		asm( "nop" );
		asm( "nop" );
	}
}

void i2c_Write(char address, bool read_write, char *data, int numofbytes)
{
	char i2cData[10];
	int DataSz;
	int Index = 0;
	unsigned char *pWrite;

	//unsigned char rx_data[10];
	char status;
	//unsigned char i2cbyte;
	DataSz = numofbytes;

	StartI2C1();	//Send the Start Bit
	IdleI2C1();		//Wait to complete
        if (read_write == 1)  //write address
        {
            MasterWriteI2C1( ((address << 1) | 0) );
            IdleI2C1();		//Wait to complete
        }
        else  //read address
        {
            MasterWriteI2C1( ((address << 1) | 1 ) );
            IdleI2C1();		//Wait to complete
        }

	while( DataSz )
	{
		MasterWriteI2C1( data[Index++] );
		IdleI2C1();		//Wait to complete

		DataSz--;

		//ACKSTAT is 0 when slave acknowledge,
		//if 1 then slave has not acknowledge the data.
		if( I2C1STATbits.ACKSTAT )
			break;
	}
	status = MasterputsI2C1(pWrite);

	if (status == -3)
		while (1);

	StopI2C1();	//Send the Stop condition
	IdleI2C1();	//Wait to complete

	// wait for eeprom to complete write process. poll the ack status
	while(1)
	{
		i2c_wait(10);

		StartI2C1();	//Send the Start Bit
		IdleI2C1();		//Wait to complete

		MasterWriteI2C1( i2cData[0] );
		IdleI2C1();		//Wait to complete

		if( I2C1STATbits.ACKSTAT == 0 )	//eeprom has acknowledged
		{
			StopI2C1();	//Send the Stop condition
			IdleI2C1();	//Wait to complete
			break;
		}

		StopI2C1();	//Send the Stop condition
		IdleI2C1();	//Wait to complete
	}
}
/*
	
	 // Now Readback several data from the serial eeprom. [3]
	 
#ifdef I2C_EEPROM_24256
	i2cData[0] = (SlaveAddress << 1) | 0;	//Device Address & WR
	i2cData[1] = 0x05;	//eeprom high address byte
	i2cData[2] = 0x41;	//eeprom low address byte
	DataSz = 3;
#endif
#ifdef I2C_EEPROM_2402
	i2cData[0] = (SlaveAddress << 1) | 0;	//Device Address & WR
	i2cData[1] = 0x11;	//eeprom low address byte
	DataSz = 2;
#endif

	StartI2C1();	//Send the Start Bit
	IdleI2C1();		//Wait to complete

	//send the address to read from the serial eeprom
	Index = 0;
	while( DataSz )
	{
		MasterWriteI2C1( i2cData[Index++] );
		IdleI2C1();		//Wait to complete

		DataSz--;

		// ACKSTAT is 0 when slave acknowledge,
		// if 1 then slave has not acknowledge the data.
		if( I2C1STATbits.ACKSTAT )
			break;
	}

	//now send a start sequence again
	RestartI2C1();	//Send the Restart condition
	i2c_wait(10);
	//wait for this bit to go back to zero
	IdleI2C1();	//Wait to complete

	MasterWriteI2C1( (SlaveAddress << 1) | 1 ); //transmit read command
	IdleI2C1();		//Wait to complete

	// read some bytes back
	status = MastergetsI2C1(lenArray(tx_data), pRead, 20);

	if (status!=0)
		while(1);

	StopI2C1();	//Send the Stop condition
	IdleI2C1();	//Wait to complete
	
	 //	End reading several bytes. [3]
	 

}
 * */