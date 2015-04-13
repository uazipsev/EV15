/* 
 * File:   buffer.h
 * Author: Igor
 *
 * Created on March 5, 2014, 6:09 PM
 */

#ifndef BUFFER_H
#define	BUFFER_H



unsigned int modulo_inc(const unsigned int value, const unsigned int modulus);
unsigned int modulo_dec(const unsigned int value, const unsigned int modulus);
void ring_buff_init(struct ringBuff* _this);
int ring_buff_size(struct ringBuff* _this);
unsigned char ring_buff_get(struct ringBuff* _this);
unsigned char ring_buff_peek(struct ringBuff* _this);
void ring_buff_put(struct ringBuff* _this, const unsigned char c);
void ring_buff_flush(struct ringBuff* _this, const int clearBuffer);



#endif	/* BUFFER_H */

