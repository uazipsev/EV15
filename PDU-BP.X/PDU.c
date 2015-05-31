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
#include "mcc_generated_files/adc.h"
#include "mcc_generated_files/memory.h"

void PDUStartup(void)
{
    //We are assuming the car just started up.
    //Lets shut down all outputs untill told otherwise
    StartUp595();
    //now enable SAS and DDS
    EnableSlavePower(SAS,ON);
    EnableSlavePower(DDS,ON);
    Update();
    //Lets pull Prev values out of memory for control
    ComputeStorageData();
}

//sets the 9v outputs as requested
void EnableSlavePower(device slave, int onof)
{
    switch(slave)
    {
        case SAS:
            SetPin595(2, 1, onof);
            break;
        case MCS:
            SetPin595(3, 1, onof);
            break;
        case DDS:
            SetPin595(2, 1, onof);
            break;
        case BMM:
            SetPin595(3, 6, onof);
            break;
        case TSS:
            SetPin595(1, 1, onof);
            break;
        case AUX:
            SetPin595(1, 6, onof);
            break;
    }
}

//sets up to read the current from the difrent mosfet drivers
void ReadCurrent(char gather)
{
    if(gather)
    {
        //read the first three
        SetPin595(1, 4, ON);
        SetPin595(1, 3, OFF);
        SetPin595(1, 2, OFF);
        SetPin595(2, 4, ON);
        SetPin595(2, 3, OFF);
        SetPin595(2, 2, OFF);
        SetPin595(3, 4, ON);
        SetPin595(3, 3, OFF);
        SetPin595(3, 2, OFF);
        Update();
        CurrentADC[0] = ADC_GetConversion(U5Multisense);
        CurrentADC[2] = ADC_GetConversion(U8Multisense);
        CurrentADC[4] = ADC_GetConversion(U10Multisense);
    }
    else
    {
        //read the second three
        SetPin595(1, 4, ON);
        SetPin595(1, 3, OFF);
        SetPin595(1, 2, ON);
        SetPin595(2, 4, ON);
        SetPin595(2, 3, OFF);
        SetPin595(2, 2, ON);
        SetPin595(3, 4, ON);
        SetPin595(3, 3, OFF);
        SetPin595(3, 2, ON);
        Update();
        CurrentADC[1] = ADC_GetConversion(U5Multisense);
        CurrentADC[3] = ADC_GetConversion(U8Multisense);
        CurrentADC[5] = ADC_GetConversion(U10Multisense);
    }
}


//pulling data out of EEPROM and getting ready to use it for our "fuse" code
void ComputeStorageData(void)
{
    for(int i = 0;i<NUMOFBYTES;i++)
    {
        data[i] = DATAEE_ReadByte(i);
    }
   Currentcomp[0] = ((data[0] << 8) | data[1]);
   Currentcomp[1] = ((data[2] << 8) | data[3]);
   Currentcomp[2] = ((data[4] << 8) | data[5]);
   Currentcomp[3] = ((data[6] << 8) | data[7]);
   Currentcomp[4] = ((data[8] << 8) | data[9]);
   Currentcomp[5] = ((data[10] << 8) | data[11]);

}

//This is our software "fuse" code to shut off outputs when uder stress
void FuseSystem()
{
    for(int i = 0;i<6;i++)
    {
        Current[i] = CurrentADC[i]*146;  //all numbers ath this point are mult by 10000
                                         //So to get real nubers divide by 10000
    }
    for(int i = 0;i<6;i++)
    {
        if(Current[i] > Currentcomp[i])
        {
            //over current condition
            
        }
    }
}

void Update(void)
{
    writeRegisters();
}