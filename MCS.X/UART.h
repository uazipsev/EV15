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
#define UART_BUFFER_SIZE_OUT 200
#define UART_BUFFER_SIZE_IN 200
#define BAUD_RATE (((CLOCK_RATE/BAUD_SET)/16)-1)

struct UART_ring_buff_In {
    unsigned char buf[UART_BUFFER_SIZE_IN];
    int head;
    int tail;
    int count;
};

struct UART_ring_buff_Out {
    unsigned char buf[UART_BUFFER_SIZE_OUT];
    int head;
    int tail;
    int count;
};

bool Transmit_stall = true;

void UART_init(void);
void UART_buff_init(struct UART_ring_buff* _this);
void UART_buff_put(struct UART_ring_buff* _this, const unsigned char c);
unsigned char UART_buff_get(struct UART_ring_buff* _this);
void UART_buff_flush(struct UART_ring_buff* _this, const int clearBuffer);
int UART_buff_size(struct UART_ring_buff* _this);
unsigned int UART_buff_modulo_inc(const unsigned int value, const unsigned int modulus);
unsigned char UART_buff_peek(struct UART_ring_buff* _this);


unsigned char Receive_peek(void);
int Receive_available(void);
unsigned char Receive_get(void);
void Send_put(unsigned char _data);

#endif	/* UART_HANDLER_H */

