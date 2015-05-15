/* 
 * File:   queue.h
 * Author: Igor
 *
 * Created on August 24, 2014, 11:04 AM
 */

#ifndef QUEUE_H
#define	QUEUE_H

class Queue_handler {
private:
#define TOP_LEVEL_QUEUE_DEPTH 5
#define SECOND_LEVEL_QUEUE_DEPTH 193

    struct Queue_member {
        unsigned char buf[SECOND_LEVEL_QUEUE_DEPTH];
        int head;
        int tail;
        int count;
    };
    
    struct Queue_top {
        struct Queue_member queue[TOP_LEVEL_QUEUE_DEPTH];
        int head;
        int tail;
        int count;
    };

    struct Queue_top send_queue;
    unsigned int queueFullErrorCounter;
    unsigned char *dma_array;
    volatile unsigned int *dmacon;
    unsigned int con_busy_mask;
    unsigned int con_en_mask;
    volatile unsigned int *dmasize;
    volatile unsigned int *dmaecon;
    unsigned int econ_force_mask;
    int module_ID;
    
    void queue_init(void);
    void queue_data_put (unsigned char data);
    unsigned char queue_data_get(void);
    unsigned int modulo_inc(const unsigned int value, const unsigned int modulus);

public:
    void queue_begin(struct dmaSettings *_settings, int module_number);
    void queue_put(unsigned char * _where, unsigned char how_many, unsigned char where, unsigned char from_where);
    bool queue_send(void);
    unsigned int fullError(void);

};

#endif	/* QUEUE_H */

