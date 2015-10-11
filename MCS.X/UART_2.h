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


#define BAUD_SET 115200
#define UART_BUFFER_SIZE 200
#define CLOCK_RATE   36000000
#define BAUD_RATE (((CLOCK_RATE/BAUD_SET)/16)-1)
//void *memset(void *s, int c, size_t n);

struct UART_ring_buff_2 {
    unsigned char buf[UART_BUFFER_SIZE];
    int head;
    int tail;
    int count;
};

extern struct UART_ring_buff_2 input_buffer_2;
extern struct UART_ring_buff_2 output_buffer_2;

bool Transmit_stall_2 = true;

extern void UART2_init(void);
void UART2_buff_init(struct UART_ring_buff_2* _this);
void UART2_buff_put(struct UART_ring_buff_2* _this, const unsigned char c);
extern unsigned char UART2_buff_get(struct UART_ring_buff_2* _this);
extern int UART2_buff_size(struct UART_ring_buff_2* _this);
extern unsigned int UART2_buff_modulo_inc(const unsigned int value, const unsigned int modulus);


//unsigned char Receive2_peek(void);
extern int Receive2_available(void);
extern unsigned char Receive2_get(void);
extern void Send2_put(unsigned char _data);

#endif	/* UART_HANDLER_H */

