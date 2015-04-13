
#include <xc.h>
#include "debug_handler.h"

#define USB_BUFFER_SIZE 200

struct USBBuff
{
    unsigned char buf[USB_BUFFER_SIZE];
    int head;
    int tail;
    int count;
};

void DebugOut::queue_put(unsigned char * _where, unsigned char how_many, unsigned char where, unsigned char from_where)
{

}