/*
 * File:   PDU.c
 * Author: Richard Johnson
 *
 * Created on May 27, 2015, 7:46 PM
 *
 * This will control the mosfet drivers and run them like a PDU
 */
#include "PDU.h"
#include "Shift595.h"
#include "Functions.h"
#include "mcc_generated_files/pin_manager.h"
#include "xc.h"

//We are assuming the car just started up.
//Lets shut down all outputs untill told otherwise
void Startup(void)
{
    StartUp595();
    //now enable SAS and DDS
    SetPin595(2, 1, HIGH);
    SetPin595(2, 6, HIGH);
    writeRegisters();
}

//when told enable
void EnableSlave(int device,int onof)
{
    switch(device)
    {
            case 0:
                SetPin595(2, 1, onof);
                break;
            case 1:
                SetPin595(2, 1, onof);
                break;
            case 2:
                SetPin595(2, 1, onof);
                break;
            case 3:
                SetPin595(2, 1, onof);
                break;
            case 4:
                SetPin595(2, 1, onof);
                break;
    }

    writeRegisters();
}