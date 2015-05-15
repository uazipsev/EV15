#include "constants.h"
#include "queue.h"
#include "FastTransfer.h"


// prototype for input ring buffer
struct ringBuff
{
    unsigned char buf[RING_BUF_SIZE];
    int head;
    int tail;
    int count;
};

// declorations for 6 input ring buffers
struct ringBuff buffer_one;
struct ringBuff buffer_two;
struct ringBuff buffer_three;
struct ringBuff buffer_four;
struct ringBuff buffer_five;
struct ringBuff buffer_six;

// declorations for dma arrays for transmit
unsigned char dma_one_array[SIZE_OF_DMA_ARRAY];
unsigned char dma_two_array[SIZE_OF_DMA_ARRAY];
unsigned char dma_three_array[SIZE_OF_DMA_ARRAY];
unsigned char dma_four_array[SIZE_OF_DMA_ARRAY];
unsigned char dma_five_array[SIZE_OF_DMA_ARRAY];
unsigned char dma_six_array[SIZE_OF_DMA_ARRAY];


// prototype for setting to pass to dma class
struct dmaSettings
{
    unsigned char *dma_array;
    volatile unsigned int *dmacon;
    unsigned int con_busy_mask;
    unsigned int con_en_mask;
    volatile unsigned int *dmasize;
    volatile unsigned int *dmaecon;
    unsigned int econ_force_mask;
};

// decloration for dma settings conaining settings for all six dams
struct dmaSettings arrayOFdmaSetting[7];


// filled with class pointers to the send class
Queue_handler * queue_pointer[7];

// object declorations for receive class
FastTransfer receive_one;
FastTransfer receive_two;
FastTransfer receive_three;
FastTransfer receive_four;
FastTransfer receive_five;
FastTransfer receive_six;

// object decloration for send class
Queue_handler DMA_one;
Queue_handler DMA_two;
Queue_handler DMA_three;
Queue_handler DMA_four;
Queue_handler DMA_five;
Queue_handler DMA_six;


