/* 
 * File:   UART.h
 * Author: Igor
 *  Application Expansion: Zac Kilburn
 *
 * Created on March 23, 2015, 11:15 AM
 * Edited on May 31, 2015
 */

#ifndef UART_HANDLER_H
#define	UART_HANDLER_H

#include "PinDef.h"

#define BAUD_SET 38400
// Note power of two buffer size
#define UART_BUFFER_SIZE_OUT 512
#define UART_BUFFER_SIZE_IN 512
#define BAUD_RATE (((CLOCK_RATE/BAUD_SET)/16)-1)

struct UART_ring_buff_In {
    long currentIndex;
    long sizeOfBuffer;
    double data[UART_BUFFER_SIZE_IN];
}RingBuffIn;

struct UART_ring_buff_Out {
    long currentIndex;
    long sizeOfBuffer;
    double data[UART_BUFFER_SIZE_OUT];
}RingBuffOut;

bool Transmit_stall = true;

void UART_init(void);
char UARTBuffInit(bool txbuff, bool rxbuff, int sizetx, int sizerx);
char UART_buff_put(char myData);
//void UART_buff_flush(struct UART_ring_buff* _this, const int clearBuffer);
//int UART_buff_size(struct UART_ring_buff* _this);
//unsigned char UART_buff_peek(struct UART_ring_buff* _this);


unsigned char Receive_peek(void);
int Receive_available(void);
unsigned char Receive_get(void);

#endif	/* UART_HANDLER_H */

