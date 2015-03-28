#include <xc.h>
#include "Define.h"
#include "Current.h"
#include "Global.h"
#include "mcc_generated_files/adc.h"

float Battery_Current;
float TempBattery_Current;
float PrevBattery_Current;

char Current_Fault()
{
    char fault = 0;      // Init fault as if there is none
    //for(int i = 0;i<9;i++)
    //{
    //    if ((BATLOW < Battery_Volt[i]) && (BATHIGH > Battery_Volt[i]))
    //    {
    //        fault = 1;   // Set fault if found! Uh-Oh!!!!
    //    }
    //}
    return fault;
}

void Current_Read()
{
  //Set the ADC interupt to start to fill in the Battery ADC Buffer
  ADC_Buffer_Point = 0;
  //Volt_Aquire = 1;  //Set global flag for ADC ISR to trigger battery volt reads
  ADCON1 = 0x80; //Set up to run ADC from VDD to Vss
  //ADC_StartConversion(Battery1);  //We need to get the ball rolling...
}

void Current_Filter()
{
   // This is a exponential moving average.
   int x;
   for(x = 0; x < 10; x++)
   {
      // Battery_Volt[x] = (BATALPHA*TempBattery_Volt[x] + ((1- BATALPHA)*PrevBattery_Volt[x]));
   }
   for(x = 0; x < 10; x++)
   {
      // PrevBattery_Volt[x] = Battery_Volt[x];
   }
}

void Current_Convert()
{
    int x;
    for(x = 0; x < 10; x++)
    {
       // TempBattery_Volt[x] = ((Battery_Adc[x]/1024)*5) + 2.5; //Normal converson w/ 2.5v offset (vref neg = 2.5v)
    }
    //Battery_Filter();
}

float Current_Get()
{
    return  Battery_Current; 
}
