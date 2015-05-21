
#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "Functions.h"
#include "PinDef.h"

int main(void)
{
    Setup();
    //TRISBbits.TRISB9 = 0;
    //delay(50);
    while (1)
    {
        Delay(500);
        LED  = 0;
        Delay(500);
        LED  = 1;
       
    }
}
