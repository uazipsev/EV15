
#include "Define.h"
//#include "Tempeture.h"
#include "Global.h"
#include "mcc_generated_files/adc.h"

float Temp_DegF[10] = 0;

char Temp_Fault()
{
    // Init fault as if there is none
    char fault = 0;
    for(int i = 0;i<9;i++)
    {
        if (TEMPHIGH > Temp_DegF[i])
        {
            fault = 1;
        }
    }

    return fault;
}

void Temp_Read()
{
  //Set the ADC interupt to start to fill in the Battery ADC Buffer
  ADC_Buffer_Point = 0;
  Temp_Aquire = 1;
  ADCON1 = 0x80; //Set up to run ADC from VDD to VSS
  ADC_StartConversion(Temp1);
}

void Temp_Filter()
{
    
}

void Temp_Convert()
{

}

int Tempeture_Get(int channelnum)
{
   return  Temp_DegF[channelnum];
}
