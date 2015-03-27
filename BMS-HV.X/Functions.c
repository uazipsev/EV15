#include <stdio.h>
#include <stdlib.h>
#include "mcc_generated_files/pin_manager.h"
#include "Functions.h"
#include <xc.h>

void Set_4051(int Channel)
{
    if (Channel & 0x01)
    {
       MUX_A_Toggle();
    }
    if ((Channel>>1) & 0x01)
    {
       MUX_B_Toggle();
    }
    if ((Channel>>2) & 0x01)
    {
       MUX_C_Toggle();
    }
}
