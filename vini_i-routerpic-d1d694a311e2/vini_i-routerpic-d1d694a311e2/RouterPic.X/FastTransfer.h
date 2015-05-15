/*
 * File:   FastTransfer.h
 * Author: Igor
 *
 * Created on August 17, 2014, 6:47 PM
 */

#ifndef FASTTRANSFER_H
#define	FASTTRANSFER_H

//the capital D is so there is no interference with the lower case d of EasyTransfer
#define Details(name) (int*)&name,sizeof(name)

class FastTransfer {
private:



    //HardwareSerial *_serial;
    unsigned char * rx_buffer; //address for temporary storage and parsing buffer
    unsigned char rx_array_inx; //index for RX parsing buffer
    unsigned char rx_len; //RX packet length according to the packet
    unsigned char calc_CS; //calculated Checksum
    unsigned char moduleAddress; // the address of this module
    unsigned char returnAddress; //the address to send the crc back to
    unsigned char maxDataAddress; //max address allowable
    int * receiveArrayAddress; // this is where the data will go when it is received
    // unsigned char * sendStructAddress; // this is where the data will be sent from
    //bool AKNAKsend; // turns the acknowledged or not acknowledged on/off
    unsigned int alignErrorCounter; //counts the align errors
    unsigned int crcErrorCounter; // counts any failed crcs
    unsigned int addressErrorCounter; // counts every time a wrong address is received
    unsigned char rx_address; //RX address received
#define polynomial 0x8C  //polynomial used to calculate crc
#define BUFFER_SIZE 64 //ring buffer size
    //#define CRC_COUNT 5 // how many AKNAKs are stored
    //#define CRC_DEPTH 3  // how many pieces of data are stored with each CRC send event
    //#define CRC_BUFFER_SIZE (CRC_COUNT * CRC_DEPTH) //crc buffer size 5 deep and 3 bytes an entry



    struct ringBuff *input_buffer;

    union stuff { // this union is used to join and disassemble integers
        unsigned char parts[2];
        unsigned int integer;
    };
    union stuff group;

    Queue_handler * queue_to_send[7];


    unsigned char ringBufS_get(struct ringBuff* _this);
    unsigned char CRC8(const unsigned char * data, unsigned char len);
    //    void sendBuf_put(struct ringBuff *_this, const unsigned char towhere, const unsigned int towhat);

    //    void ringBufS_flush(struct ringBuff* _this, const int clearBuffer);
    unsigned int modulo_inc(const unsigned int value, const unsigned int modulus);
    //
    //    void CRCcheck(void);
    int ringBufS_size(struct ringBuff* _this);


public:
    void begin(struct ringBuff *buff, Queue_handler * queue_to_hand_over[7]);
    //void sendData(unsigned char whereToSend);
    bool receiveData();
    //void ToSend(const unsigned char where, const unsigned int what);
    //unsigned char AKNAK(unsigned char module);
    unsigned int alignError(void);
    unsigned int CRCError(void);
    unsigned int addressError(void);
};




#endif	/* FASTTRANSFER_H */

