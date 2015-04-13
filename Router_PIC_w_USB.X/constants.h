/* 
 * File:   constants.h
 * Author: Igor
 *
 * Created on August 17, 2014, 7:20 PM
 */

#ifndef CONSTANTS_H
#define	CONSTANTS_H

#define SYS_FREQ 80000000 // system frequency
#define DESIRED_BAUD_RATE 57600
#define BAUD_RATE ((SYS_FREQ / (16 * DESIRED_BAUD_RATE) - 1)

#define RING_BUF_SIZE 64  // size of the incoming ring buffer

#define SIZE_OF_DMA_ARRAY 200

#endif	/* CONSTANTS_H */

