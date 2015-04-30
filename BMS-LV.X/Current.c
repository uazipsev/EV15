#include <xc.h>
#include "Define.h"
#include "Current.h"
#include "Global.h"
#include "mcc_generated_files/adc.h"

float Battery_Current[10] = 0;
float TempBattery_Current[10] = 0;
float PrevBattery_Current[10] = 0;

char Current_Fault()
{
    char fault = 0;      // Init fault as if there is none
    float temp = 0;
    for(int i = 0;i<9;i++)
    {
        temp += Battery_Current[i];
    }
    temp = temp/10.0;
    for(int i = 0;i<9;i++)
    {
        if ((CURRENTHIGH < Battery_Current[i]) && (CURRENTHIGH < temp)) // I need to add the ability to check other packets
        {
            fault = 1;
        }
    }
    return fault;
}

void Current_Read()
{
  //Set the ADC interupt to start to fill in the Battery ADC Buffer
  ADC_Buffer_Point = 0;
  Current_Aquire = 1;  //Set global flag for ADC ISR to trigger battery volt reads
  ADCON1 = 0x80; //Set up to run ADC from VDD to Vss
  ADC_StartConversion(Asen);  //We need to get the ball rolling...
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
        TempBattery_Current[x] = ((Battery_Adc[x]/1024)*5) + 2.5; //Normal converson w/ 2.5v offset (vref neg = 2.5v)
    }
    Current_Filter();
}

float Current_Get()
{
    float temp = 0;
    for(int i = 0;i<9;i++)
    {
        temp += Battery_Current[i];
    }
    temp = temp/10.0;
    return  temp;
}
