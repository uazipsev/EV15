/* 
 * File:   variables.h
 * Author: Igor
 *
 * Created on September 12, 2014, 6:07 PM
 */

#ifndef VARIABLES_H
#define	VARIABLES_H

#ifdef	__cplusplus
extern "C" {
#endif

    extern struct ringBuff buffer_one;
    extern struct ringBuff buffer_two;
    extern struct ringBuff buffer_three;
    extern struct ringBuff buffer_four;
    extern struct ringBuff buffer_five;
    extern struct ringBuff buffer_six;


    extern unsigned char dma_one_array[SIZE_OF_DMA_ARRAY];
    extern unsigned char dma_two_array[SIZE_OF_DMA_ARRAY];
    extern unsigned char dma_three_array[SIZE_OF_DMA_ARRAY];
    extern unsigned char dma_four_array[SIZE_OF_DMA_ARRAY];
    extern unsigned char dma_five_array[SIZE_OF_DMA_ARRAY];
    extern unsigned char dma_six_array[SIZE_OF_DMA_ARRAY];

    extern struct dmaSettings arrayOFdmaSetting[7];

    
    extern Queue_handler * queue_pointer[7];


#ifdef	__cplusplus
}
#endif



    extern FastTransfer receive_one;
    extern FastTransfer receive_two;
    extern FastTransfer receive_three;
    extern FastTransfer receive_four;
    extern FastTransfer receive_five;
    extern FastTransfer receive_six;

    extern Queue_handler DMA_one;
    extern Queue_handler DMA_two;
    extern Queue_handler DMA_three;
    extern Queue_handler DMA_four;
    extern Queue_handler DMA_five;
    extern Queue_handler DMA_six;

#endif	/* VARIABLES_H */

