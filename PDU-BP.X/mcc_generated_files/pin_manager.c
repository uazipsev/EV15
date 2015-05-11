

#include <xc.h>
#include "pin_manager.h"

void PIN_MANAGER_Initialize(void)
{
    LATA = 0x00;
    TRISA = 0xE7;
    ANSELA = 0x27;

    LATB = 0x03;
    TRISB = 0xFC;
    ANSELB = 0x3C;
    WPUB = 0x00;

    LATC = 0x00;
    TRISC = 0xDF;
    ANSELC = 0x1C;

    LATD = 0x00;
    TRISD = 0x1F;
    ANSELD = 0x1F;

    LATE = 0x00;
    TRISE = 0x07;
    ANSELE = 0x07;

    INTCON2bits.nRBPU = 0x01;

        
}
/**
 End of File
*/