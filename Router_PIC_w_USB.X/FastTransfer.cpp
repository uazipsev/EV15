#include <xc.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "queue.h"
#include "FastTransfer.h"

// struct for ring buffer

struct ringBuff
{
    unsigned char buf[BUFFER_SIZE];
    int head;
    int tail;
    int count;
};


//Captures address of receive array, the max data address, the address of the module, true/false if AKNAKs are wanted and the Serial address

void FastTransfer::begin(struct ringBuff *buff, Queue_handler * queue_to_hand_over[7])
{

    input_buffer = buff; // points to where the input buffer is
    int t;
    for (t = 1; t <= 6; t++) // moves the settings to internal variables
    {
        queue_to_send[t] = queue_to_hand_over[t];
    }

}

//CRC Calculator

unsigned char FastTransfer::CRC8(const unsigned char * data, unsigned char len)
{
    unsigned char crc = 0x00;
    while (len--)
    {
        unsigned char extract = *data++;
        for (unsigned char tempI = 8; tempI; tempI--)
        {
            unsigned char sum = (crc ^ extract) & 0x01;
            crc >>= 1;
            if (sum)
            {
                crc ^= polynomial;
            }
            extract >>= 1;
        }
    }
    return crc;
}

bool FastTransfer::receiveData()
{

    //start off by looking for the header bytes. If they were already found in a previous call, skip it.
    if (rx_len == 0)
    {
        //this size check may be redundant due to the size check below, but for now I'll leave it the way it is.
        if (ringBufS_size(input_buffer) > 4)
        {
            //this will block until a 0x06 is found or buffer size becomes less then 3.
            while (ringBufS_get(input_buffer) != 0x06)
            {
                //This will trash any preamble junk in the serial buffer
                //but we need to make sure there is enough in the buffer to process while we trash the rest
                //if the buffer becomes too empty, we will escape and try again on the next call
                alignErrorCounter++; //increments the counter whenever a byte is trashed
                if (ringBufS_size(input_buffer) < 5) //if true beak out because not enough data in buffer
                {
                    return false;
                }
            }
            if (ringBufS_get(input_buffer) == 0x85) // if true second header bite found
            {
                rx_address = ringBufS_get(input_buffer); // pulls the address
                returnAddress = ringBufS_get(input_buffer); // pulls where the message came from
                rx_len = ringBufS_get(input_buffer); // pulls the length
                // makes sure that the address is in range allowed
                if ((rx_address > 6) || (rx_address < 1))
                {
                    rx_len = 0;
                    addressErrorCounter++; // increments a counter whenever the wrong address is received
                    //if the address does not match the buffer is flushed for the size of
                    //the data packet plus one for the CRC
                    for (int u = 0; u <= (rx_len + 3); u++)
                    {
                        ringBufS_get(input_buffer);
                    }
                    return false;
                }
                // if the address matches the a dynamic buffer is created to store the received data
                rx_buffer = (unsigned char*) malloc(rx_len + 1);
                if (rx_buffer == NULL)
                { //oops!
                    while (1);
                }
            }
        }
    }

    //we get here if we already found the header bytes, the address matched what we know, and now we are byte aligned.
    if (rx_len != 0)
    {
        // pull all the data out of the buffer
        while (ringBufS_size(input_buffer) && rx_array_inx <= rx_len)
        {
            rx_buffer[rx_array_inx++] = ringBufS_get(input_buffer);
        }


        if (rx_len == (rx_array_inx - 1)) // if true go the whole message
        {
            //last unsigned char is CS
            calc_CS = CRC8(rx_buffer, rx_len);



            if (calc_CS == rx_buffer[rx_array_inx - 1]) // if true CRC good
            {
                // place the recieved data in the correct send queue
                queue_to_send[rx_address]->queue_put(rx_buffer, rx_len, rx_address, returnAddress);
                // reset to get ready for the next message
                rx_len = 0;
                rx_array_inx = 0;
                free(rx_buffer);
                return true;
            } else
            {
                crcErrorCounter++; //increments the counter every time a crc fails
                //failed checksum, need to clear this out
                rx_len = 0;
                rx_array_inx = 0;
                free(rx_buffer);
                return false;
            }
        }
    }
    return false;
}


//pulls info out of the send buffer in a first in first out fashion

unsigned char FastTransfer::ringBufS_get(struct ringBuff* _this)
{
    unsigned char c;
    if (_this->count > 0) // if true there is data to retireive
    {
        c = _this->buf[_this->tail]; //get the data
        _this->tail = modulo_inc(_this->tail, BUFFER_SIZE); // increment tail
        --_this->count; // decrement count
    } else
    {
        c = 0; // if nothing to get return zero
    }
    return (c);
}

int FastTransfer::ringBufS_size(struct ringBuff* _this)
{
    return (_this->count);
}


// increments counters for the buffer functions

unsigned int FastTransfer::modulo_inc(const unsigned int value, const unsigned int modulus)
{
    unsigned int my_value = value + 1;
    if (my_value >= modulus)
    {
        my_value = 0;
    }
    return (my_value);
}


//returns align error

unsigned int FastTransfer::alignError(void)
{
    return alignErrorCounter;
}


//returns CRC error

unsigned int FastTransfer::CRCError(void)
{
    return crcErrorCounter;
}


//returns address error

unsigned int FastTransfer::addressError(void)
{
    return addressErrorCounter;
}

