#include <xc.h>
#include <string.h>
#include "queue.h"

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


// function runs to iniciate the queue system
// the function is handed all the tools it needs to work the dma for sending

void Queue_handler::queue_begin(struct dmaSettings *_settings, int module_number)
{
    // move settings to internal variables
    dma_array = _settings[module_number].dma_array;
    dmacon = _settings[module_number].dmacon;
    con_busy_mask = _settings[module_number].con_busy_mask;
    con_en_mask = _settings[module_number].con_en_mask;
    dmasize = _settings[module_number].dmasize;
    dmaecon = _settings[module_number].dmaecon;
    econ_force_mask = _settings[module_number].econ_force_mask;
    module_ID = module_number;

    // flush the queue buffer
    queue_init();
}


// set everything to zeros
void Queue_handler::queue_init(void)
{
    send_queue.head = 0;
    send_queue.tail = 0;
    send_queue.count = 0;
    int i;
    for (i = 0; i < TOP_LEVEL_QUEUE_DEPTH; i++)
    {
        send_queue.queue[i].count = 0;
        send_queue.queue[i].head = 0;
        send_queue.queue[i].tail = 0;
        memset(send_queue.queue[i].buf, 0, SECOND_LEVEL_QUEUE_DEPTH);
    }

}

void Queue_handler::queue_put(unsigned char * what, unsigned char how_many, unsigned char where, unsigned char from_where)
{
    
    if (send_queue.count < TOP_LEVEL_QUEUE_DEPTH)
    {
        queue_data_put(0x06);
        queue_data_put(0x85);
        queue_data_put(where);
        queue_data_put(from_where);
        queue_data_put(how_many);
        int i;
        for (i = 0; i < (how_many + 1); i++)
        {
            queue_data_put(what[i]);
        }
        send_queue.head = modulo_inc(send_queue.head, TOP_LEVEL_QUEUE_DEPTH);
        send_queue.count++;
    } else
    {
        queue_data_put(0x06);
        queue_data_put(0x85);
        queue_data_put(where);
        queue_data_put(from_where);
        queue_data_put(how_many);
        int i;
        for (i = 0; i <= how_many; i++)
        {
            queue_data_put(what[i]);
        }
        send_queue.head = modulo_inc(send_queue.head, TOP_LEVEL_QUEUE_DEPTH);
        send_queue.tail = modulo_inc(send_queue.tail, TOP_LEVEL_QUEUE_DEPTH);
        queueFullErrorCounter++; // because the queue is full to use this functions
    }
}

void Queue_handler::queue_data_put(unsigned char data)
{
    if (send_queue.queue[send_queue.head].count < SECOND_LEVEL_QUEUE_DEPTH)
    {
        send_queue.queue[send_queue.head].buf[send_queue.queue[send_queue.head].head] = data;
        send_queue.queue[send_queue.head].head = modulo_inc(send_queue.queue[send_queue.head].head, SECOND_LEVEL_QUEUE_DEPTH);
        send_queue.queue[send_queue.head].count++;
    } else
    {
        send_queue.queue[send_queue.head].buf[send_queue.queue[send_queue.head].head] = data;
        send_queue.queue[send_queue.head].head = modulo_inc(send_queue.queue[send_queue.head].head, SECOND_LEVEL_QUEUE_DEPTH);
        send_queue.queue[send_queue.head].tail = modulo_inc(send_queue.queue[send_queue.head].tail, SECOND_LEVEL_QUEUE_DEPTH);
    }
}

unsigned char Queue_handler::queue_data_get(void)
{
    unsigned char dat;
    if (send_queue.count > 0)
    {
        if (send_queue.queue[send_queue.tail].count > 0)
        {
            dat = send_queue.queue[send_queue.tail].buf[send_queue.queue[send_queue.tail].tail];
            send_queue.queue[send_queue.tail].tail--;
            send_queue.queue[send_queue.tail].count--;
        } else
        {
            dat = 0;
        }
    } else
    {
        dat = 0;
    }
    return dat;
}

unsigned int Queue_handler::modulo_inc(const unsigned int value, const unsigned int modulus)
{
    unsigned int my_value = value + 1;
    if (my_value >= modulus)
    {
        my_value = 0;
    }
    return (my_value);
}

bool Queue_handler::queue_send(void)
{
    if (send_queue.count > 0) // if send queue is empty no need to send
    {
        if ((*dmacon & con_busy_mask) == 0) // if dma is busy then no need to send
        {
            // if all the checks pass populate the dma buffer, set the size, enable and force a send
            int g;
            int h = send_queue.queue[send_queue.tail].count;
            for (g = 0; g < h; g++)
            {
                dma_array[g] = send_queue.queue[send_queue.tail].buf[g];
            }
                *dmasize = h;
                *dmacon |= con_en_mask;
                *dmaecon |= econ_force_mask;
                // flush send queue
                send_queue.queue[send_queue.tail].count = 0;
                send_queue.queue[send_queue.tail].head = 0;
                send_queue.queue[send_queue.tail].tail = 0;
                memset(send_queue.queue[send_queue.tail].buf, 0, SECOND_LEVEL_QUEUE_DEPTH);
                //tidy up tail and counter
                send_queue.count--;
                send_queue.tail = modulo_inc(send_queue.tail, TOP_LEVEL_QUEUE_DEPTH);
                return true;

            
        } else
        {
            return false;
        }
    } else
    {
        return false;
    }

}

// returns the queue full error
unsigned int Queue_handler::fullError(void)
{
    return queueFullErrorCounter;
}