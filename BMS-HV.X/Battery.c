#include <xc.h>
#include "Define.h"
#include "Battery.h"
#include "Global.h"
#include "mcc_generated_files/adc.h"

float Battery_Volt[10];

char Battery_Fault()
{
    // Init fault as if there is none
    char fault = 0;
    for(int i = 0;i<9;i++)
    {
        if ((BATLOW < Battery_Volt[i]) && (BATHIGH > Battery_Volt[i]))
        {
            fault = 1;
        }
    }

    return fault;
}

void Battery_Read()
{
  //Set the ADC interupt to start to fill in the Battery ADC Buffer
  ADC_Buffer_Point = 0;
  Volt_Aquire = 1;
  ADCON1 = 0x81; //Set up to run ADC from VDD to Vref- (2.5v)
  ADC_StartConversion(Battery1);
}

void Battery_Filter()
{
    
}

void Battery_Convert()
{

}

float Battery_Get(int channelnum)
{
   return  Battery_Volt[channelnum];
}

