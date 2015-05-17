#include <xc.h>
#include <stdbool.h>
#include "I2C_API.h"
#include <i2c.h>

#define USE_AND_OR	// To enable AND_OR mask setting for I2C.
#define I2C_BRG	((Fcy/2/Fsck)-1)


void I2C1Init(void)
{
    I2C1CONbits.I2CEN = 1;   //enable I2c
    I2C1CONbits.I2CSIDL = 1; //Stop module in idle mode
    I2C1CONbits.IPMIEN = 0;  //diable IPMIEN
    I2C1CONbits.A10M = 0;    //7bit address
    I2C1CONbits.DISSLW = 1;  //Shut off slew rate
    I2C1CONbits.SMEN = 0;    //disable SMbus Logic levels
    I2C1CONbits.ACKDT = 0;   //Send ACk during Ack


}

void I2C1ACK(void)
{
        I2C1CONbits.ACKEN = 1;   //Send ACK
}

void I2C1RXEN(void)
{
    I2C1CONbits.RCEN = 1;    //RX EN
}


void Init_I2C_one(void)
{
    I2C1BRG = 591; // set baud rate 
    I2C1CONbits.I2CEN = 1; // enable i2c one
}

/*
void i2c_wait(unsigned int cnt)
{
	while(--cnt)
	{
		asm( "nop" );
		asm( "nop" );
	}
}

unsigned char SlaveAddress;
	char i2cData[10];
	int DataSz;
	int Index = 0;
	unsigned char *pWrite, *pRead;
	unsigned char tx_data[] = {'P', 'I', 'C', '2', '4', 'F', '\0'};

	unsigned char rx_data[10];
	char status;
	unsigned char i2cbyte;

	//Enable channel


	SlaveAddress = 0x50;	//0b1010000 Serial EEPROM address

	i2cData[0] = (SlaveAddress << 1) | 0;	//Device Address & WR
	i2cData[1] = 0x05;	//eeprom high address byte
	i2cData[2] = 0x40;	//eeprom low address byte
	i2cData[3] = 0xAC;	//data to write
	DataSz = 4;


	StartI2C1();	//Send the Start Bit
	IdleI2C1();		//Wait to complete

	while( DataSz )
	{
		MasterWriteI2C1( i2cData[Index++] );
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

	i2cData[0] = (SlaveAddress << 1) | 0;	//Device Address & WR
	i2cData[1] = 0x05;	//eeprom high address byte
	i2cData[2] = 0x40;	//eeprom low address byte
	DataSz = 3;


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

	i2cbyte = MasterReadI2C1();	// read one byte

	StopI2C1();	//Send the Stop condition
	IdleI2C1();	//Wait to complete
	
	 //	End reading one byte. [2]
	 

	// verify write and read I2C EEPROM (single byte)
	if( i2cbyte != 0xAC )
		while(1); //error: verify failed

	
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
*/