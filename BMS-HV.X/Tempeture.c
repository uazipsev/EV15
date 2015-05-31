
#include "Define.h"
//#include "Tempeture.h"
#include "Global.h"
#include "mcc_generated_files/adc.h"
#include "../math.h"

float Temp_DegF[10] = 0;
float TmpTemp_DegF[10] = 0;
float PrevTemp_DegF[10] = 0;

/*******************************************************************
 * @brief           reads in temp and checks over temp condition
 * @return          over temp fault condition
 *******************************************************************/
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


/*******************************************************************
 * @brief           Strts ADC temp read in ISR
 * @return          nothing
 *******************************************************************/
void Temp_Read()
{
  //Set the ADC interupt to start to fill in the Battery ADC Buffer
  ADC_Buffer_Point = 0;
  Temp_Aquire = 1;
  ADCON1 = 0x80; //Set up to run ADC from VDD to VSS
  ADC_StartConversion(Temp1);
}

/*******************************************************************
 * @brief           filters data to give clean values
 * @return          nothing
 *******************************************************************/
void Temp_Filter()
{
   // This is a exponential moving average.
   int x;
   for(x = 0; x < 10; x++)
   {
       Temp_DegF[x] = (TEMPALPHA*TmpTemp_DegF[x] + ((1- TEMPALPHA)*PrevTemp_DegF[x]));
   }
   for(x = 0; x < 10; x++)
   {
       PrevTemp_DegF[x] = Temp_DegF[x];
   }
}

/*******************************************************************
 * @brief           steinhart NTC ADC to temp in F
 * @return          nothing
 * @note            may want to optimize this 
 *******************************************************************/
void Temp_Convert()
{
   int x;
   float steinhart;
   for(x = 0; x < 10; x++)
   {
       steinhart = (SERIESRESISTOR / ((1023 / Temp_Adc[x]) - 1)) / THERMISTORNOMINAL;  //Convert ADC counts to resistance/Ro
       steinhart = log(steinhart);                       // ln(R/Ro)
       steinhart /= BCOEFFICIENT;                        // 1/B * ln(R/Ro)
       steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
       steinhart = 1.0 / steinhart;                      // Invert
       steinhart -= 273.15;                              // convert to C
       steinhart = (steinhart*1.800) + 32.00;            // convert to F
       TmpTemp_DegF[x] = steinhart;
   }
   Temp_Filter();
}

/*******************************************************************
 * @brief           getter for temps
 * @param[in]       channelnum - What of 10 inputs to read
 * @return          temp value in F
 *******************************************************************/
float Tempeture_Get(int channelnum)
{
   return  Temp_DegF[channelnum];
}