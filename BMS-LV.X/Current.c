#include <xc.h>
#include "Define.h"
#include "Current.h"
#include "Global.h"
#include "mcc_generated_files/adc.h"

float Battery_Current[10] = 0;
float TempBattery_Current[10] = 0;
float PrevBattery_Current[10] = 0;
float Current_Mean = 0;

char Current_Fault()
{
    int fault = 0;      // Init fault as if there is none
    float temp = 0;
    for(int i = 0;i<9;i++)
    {
        temp += Battery_Current[i];
    }
    temp = temp/10.0;
    Current_Mean = temp;
    for(int i = 0;i<9;i++)
    {
        if ((CURRENTHIGH < Battery_Current[i]) && (CURRENTHIGH < temp)) // I need to add the ability to check other packets
        {
            fault++;
        }
    }
    if(fault > NUMFALTS)
    {
        fault = 1;
    }
    else
    {
        fault = 0;
    }
    return fault;
}

void Current_Read()
{
  //Set the ADC interupt to start to fill in the Battery ADC Buffer
  ADC_Buffer_Point = 0;
  Current_Aquire = 1;  //Set global flag for ADC ISR to trigger battery volt reads
  ADCON1 = 0x80; //Set up to run ADC from VDD to Vss
  ADC_GetConversion(Asen);
}

void Current_Filter()
{
   // This is a exponential moving average.
   int x;
   for(x = 0; x < 10; x++)
   {
      Battery_Current[x] = (BATALPHA*TempBattery_Current[x] + ((1- BATALPHA)*PrevBattery_Current[x]));
   }
   for(x = 0; x < 10; x++)
   {
      PrevBattery_Current[x] = Battery_Current[x];
   }
}

void Current_Convert()
{
    int x;
    for(x = 0; x < 10; x++)
    {
        TempBattery_Current[x] = ((((Current_Adc[x]/1024)*500)-2500)/66); //Normal converson w/ 2.5 offset and 66mV/A
    }
    Current_Filter();
}

float Current_Get()
{
    return  Current_Mean;
}
