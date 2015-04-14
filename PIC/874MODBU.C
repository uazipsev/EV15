#include "874modbu.h"
#define SlaveAddress 1

int isrEnd,readEnd;


bank1 unsigned char buffer[74];

union transform{
struct twoBytes{
	unsigned char lowByte;
	unsigned char highByte;
        }bytes;
unsigned int integer;
}T;       
	
void delay(unsigned int time)
{
unsigned int i,j;	
for (i = 0; i<=time; i++)
{
	j= 1000;
	while (j) j--;
}
}	
	

bit DataArrive = 0;
bit stop = 0;
void setRS(void) //RS setting
{
BRGH = 0;	
SPBRG = 31;     // baud rate  9600 for 20 MHz
SYNC = 0;	
SPEN = 1;	// serial port pins ON 
CREN = 1;	
SREN = 0;	
TXIE = 0;	
RCIE = 0;	
TX9  = 0;	
RX9  = 0;	
TXEN = 1;	
}

void startI2C(void)
{
SEN = 1;
while (SEN);
}

void stopI2C(void)
{
PEN = 1;
while (PEN);
}

unsigned char readRS(vid)
{
	while(!RCIF) continue;
	return RCREG;
}
	
void writeRS(unsigned char c)
{
TXREG = c;
TXEN = 1;
while (!TRMT);
}

unsigned char readI2C(void)
{
isrEnd = 0;
while(!isrEnd);
PEN = 1;
while (PEN);
return SSPBUF;
}	

void writeI2C(unsigned char data)
{
isrEnd = 0;
SSPBUF = data;
while (!isrEnd);
while (ACKSTAT);
}


bit  CRC16(unsigned int dataLength,char check) //CRC 16 for modbus checksum
{
unsigned int CheckSum;
unsigned int j;
unsigned char lowCRC;
unsigned char highCRC;
unsigned short i;
CheckSum = 0xffff;
for (j=0; j<dataLength; j++)
{
CheckSum = CheckSum^(unsigned int)buffer[j];
for(i=8;i>0;i--)
	if((CheckSum)&0x0001)
	CheckSum = (CheckSum>>1)^0xa001;
	else
	CheckSum>>=1;
}	
highCRC = CheckSum>>8;
CheckSum<<=8;
lowCRC = CheckSum>>8;
if (check==1){	
if ( (buffer[dataLength+1] == highCRC) & (buffer[dataLength] == lowCRC ))	
  return 1;
else
  return 0;
}
else
{  
buffer[dataLength] = lowCRC;
buffer[dataLength+1] = highCRC;
return 1; 	
}
	
}
	
void readRegResponse(void) //response for modbus 03 function (read registers)
{
unsigned char i;
T.bytes.lowByte = buffer[3]; 
T.bytes.highByte = buffer[2]; 
T.integer*=2;
buffer[2] = buffer[5]*2;
for (i=0; i<buffer[2]; i++)
     {
	startI2C();
	writeI2C(0xA0);
	writeI2C(T.bytes.highByte);
	writeI2C(T.bytes.lowByte);
	stopI2C();
	startI2C();
	writeI2C(0xA1);
	RCEN = 1;
	buffer[i+3] = readI2C();
	RCEN = 0;
        T.integer++;
      }
CRC16(buffer[2]+3,0);
for (i=0; i<buffer[2] + 5; i++)
writeRS(buffer[i]);
}	

void writeBadRequest(unsigned char error) //response for error in modbus poll
{
unsigned char i;	
if (error>0)
{
buffer[1]+=0x80;
buffer[2]=error;
CRC16(3,0);
for (i=0; i<5; i++)
writeRS(buffer[i]);
}
}	

void writeRegResponse(void) //response for modbus 16 function preset multiple registers
{
unsigned char i;
T.bytes.lowByte = buffer[3]; 
T.bytes.highByte = buffer[2]; 
T.integer*=2;
for (i=0; i<buffer[6]; i++)
     {
	startI2C();
	writeI2C(0xA0);
	writeI2C(T.bytes.highByte);
	writeI2C(T.bytes.lowByte);
	writeI2C(buffer[i+7]);
	stopI2C();
        T.integer++;
        delay(1);
      }
CRC16(6,0);
for (i=0; i<8; i++)
writeRS(buffer[i]);
}	

bit CheckRSInBuffer(void)
{
unsigned int j = 0;
while((!RCIF) && (j < 30000)) j++;
	return RCIF;
}

unsigned char  ReadMBFrame()
{
unsigned int counter = 0;
unsigned int aux;
stop = 0;
while (!stop) 
   if(!CheckRSInBuffer())
         stop = 1;
   else
        {
	if (counter<=73)        
        buffer[counter] = RCREG;
        counter++;
        }
if ((buffer[1] == 16)&(((unsigned int) buffer[6] + 9)!=counter)) return 2; //wrong  nr of registers
if (counter > 74) return 2; //to many bytes in frame       
if (counter < 8) return 0; //to few bytes frame
if (buffer[0] != SlaveAddress) return 0; //wrong address
if ((buffer[1] != 3) & (buffer[1] != 16))return 1; //wrong modbus function
aux = (unsigned int)buffer[2] * 255 + (unsigned int)buffer[3] + (unsigned int)buffer[4]*255 +(unsigned int)buffer[5];
if (aux > 8000) return 2; // to many registers
if ((buffer[4]>0)|( buffer[5] > 32)) return 2; // to many registers
if( CRC16(counter - 2,1)) 
   return buffer[1]; //OK
else
   return 0;   //bad CRC
    
  
}

		
void setISR(void) /*Sets ISR bits */
{
GIE = 1;
PEIE = 1;
RCIE = 0;
SSPIE = 1;
EEIE = 1;
}

void I2CInitialize(void)
{
SSPEN = 1;
SSPM3 = 1;
SSPM2 = 0;
SSPM1 = 0;
SSPM0 = 0;
SSPADD = 12;
}

void interrupt isr(void)
{
if (SSPIF) 	
{
SSPIF = 0;	
isrEnd = 1;
}
}

void main(void)
{
unsigned char c;
c = 1;
TRISB = 0xE0;        
TRISC = 0xF8;
RB1 = 0;
RB2 = 0; 
RC3 = 1;
RC4 = 1;
setISR();
I2CInitialize();
setRS();
for(;;)
{
if (RCIF) {
c =ReadMBFrame();
if (c == 3) 
   readRegResponse();	
else
   if (c==16)
      writeRegResponse();
   else
      writeBadRequest(c);
}
	
}  

}	
