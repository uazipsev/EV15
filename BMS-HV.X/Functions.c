 #include <stdio.h>
#include <stdlib.h>
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/mcc.h"
#include <xc.h>

#include "Functions.h"

/*******************************************************************
 * @brief           Controls 74 series 4051 Analog mux
 * @param[in]       Channel - what NTC channel to read
 * @return          nothing
 * @note            Like to make this fcn better
 *******************************************************************/
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

/*******************************************************************
 * @brief           Delay control
 * @param[in]       d_lenth - how long to wait in 1 ms intervals
 * @return          nothing
 * @note            used because of xc.h fcn limitations
 *******************************************************************/
void Delay(long int d_lenth)
{
    long int wait = 0;
    for(wait;wait<d_lenth;wait++)
    {
        __delay_ms(1);
    }
}