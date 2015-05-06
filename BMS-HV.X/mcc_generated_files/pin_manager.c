

#include <xc.h>
#include "pin_manager.h"

void PIN_MANAGER_Initialize(void)
{
    LATA = 0x00;
    TRISA = 0xAE;
    ANSELA = 0x2E;

    LATB = 0x00;
    TRISB = 0xF4;
    ANSELB = 0x34;
    WPUB = 0x00;

    LATC = 0x08;
    TRISC = 0xC4;
    ANSELC = 0x04;

    LATD = 0x00;
    TRISD = 0xD1;
    ANSELD = 0xD1;

    LATE = 0x00;
    TRISE = 0x05;
    ANSELE = 0x05;

    INTCON2bits.nRBPU = 0x01;

        
}
/**
 End of File
*/