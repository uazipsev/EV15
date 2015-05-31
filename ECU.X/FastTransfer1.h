/* 
 * File:   FastTransfer1.h
 * Author: User
 *
 * Created on May 31, 2015, 2:09 PM
 */

#ifndef FASTTRANSFER1_H
#define	FASTTRANSFER1_H

#ifdef	__cplusplus
extern "C" {
#endif

//the capital D is so there is no interference with the lower case d of EasyTransfer
#define Details(name) (int*)&name,sizeof(name)


#define polynomial 0x8C  //polynomial used to calculate crc
#define BUFFER_SIZE 400 //ring buffer size
#define CRC_COUNT 5 // how many AKNAKs are stored
#define CRC_DEPTH 3  // how many pieces of data are stored with each CRC send event
#define CRC_BUFFER_SIZE (CRC_COUNT * CRC_DEPTH) //crc buffer size 5 deep and 3 bytes an entry

//PUBLIC METHODS/VARIABLES HERE
void begin1(volatile int * ptr, unsigned char maxSize, unsigned char givenAddress, bool error, void (*stufftosend)(unsigned char), unsigned char (*stufftoreceive)(void),int (*stuffavailable)(void), unsigned char (*stuffpeek)(void));
void sendData1(unsigned char whereToSend);
bool receiveData1();
void ToSend1(const unsigned char where, const unsigned int what);
volatile int receiveArray1[20];









#ifdef	__cplusplus
}
#endif

#endif	/* FASTTRANSFER1_H */

