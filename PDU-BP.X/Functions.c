#include "functions.h"
#include "xc.h"
#include "mcc_generated_files/mcc.h"

void Delay(long int wait)
{
    long int i = 0;
    for(;wait>i;i++)
    {
        __delay_ms(1);
    }
}