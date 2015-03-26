

#include <xc.h>
#include "adc.h"
#include "../Global.h"
#include "../Functions.h"


/**
  Section: ADC Module APIs
*/

void ADC_Initialize(void)
{
    // set the ADC to the options selected in the User Interface
    
    // GO_nDONE stop; ADON enabled; CHS AN0; 
    ADCON0 = 0x01;
    
    // PVCFG VDD; TRIGSEL CTMU; NVCFG VSS; 
    ADCON1 = 0x80;
    
    // ADFM left; ADCS FOSC/32; ACQT 2; 
    ADCON2 = 0x0A;
    
    // ADRESL 0x0; 
    ADRESL = 0x00;
    
    // ADRESH 0x0; 
    ADRESH = 0x00;
    
    // Enabling ADC interrupt.
    PIE1bits.ADIE = 1;
}

void ADC_StartConversion(adc_channel_t channel)
{
    // select the A/D channel
    ADCON0bits.CHS = channel;

    // Turn on the ADC module
    ADCON0bits.ADON = 1;

    
    // Start the conversion
    ADCON0bits.GO_nDONE = 1;
}

bool ADC_IsConversionDone()
{
    // Start the conversion
    return (!ADCON0bits.GO_nDONE);
}

adc_result_t ADC_GetConversionResult(void)
{
    // Conversion finished, return the result
    return ((ADRESH << 8) + ADRESL);
}

adc_result_t ADC_GetConversion(adc_channel_t channel)
{
    // Select the A/D channel
    ADCON0bits.CHS = channel;

    // Turn on the ADC module
    ADCON0bits.ADON = 1;


    // Start the conversion
    ADCON0bits.GO_nDONE = 1;

    // Wait for the conversion to finish
    while (ADCON0bits.GO_nDONE)
    {
    }
    
    // Conversion finished, return the result
    return ((ADRESH << 8) + ADRESL);
}

void ADC_ISR(void)
{
    // Clear the ADC interrupt flag
    PIR1bits.ADIF = 0;
    int ADC_Result = 0;
    if (Temp_Aquire){
        //Do the temp sensor ADC
        ADC_Result = ADC_GetConversionResult();
        switch ( ADC_Buffer_Point )
        {
            case 0:
              Temp_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Temp1);
              break;
            case 1:
              Temp_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Temp1);
              break;
            case 2:
              Temp_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Temp1);
              break;
            case 3:
              Temp_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Temp1);
              break;
            case 4:
              Temp_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Temp1);
              break;
            case 5:
              Temp_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Temp1);
              break;
            case 6:
              Temp_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Temp1);
              break;
            case 7:
              Temp_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Temp1);
              break;
            case 8:
              Temp_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Temp2);
              break;
            case 9:
              Temp_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Temp2);
              break;
            case 10:
              Temp_Aquire = 0;
              Temp_Done = 1;
              break;
}
        ADC_Buffer_Point++;
    }
    if (Volt_Aquire){
        //Do the Batt sensor ADC
        ADC_Result = ADC_GetConversionResult();
        switch ( ADC_Buffer_Point )
        {
            case 0:
              Battery_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Battery1);
              break;
            case 1:
              Battery_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Battery2);
              break;
            case 2:
              Battery_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Battery3);
              break;
            case 3:
              Battery_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Battery4);
              break;
            case 4:
              Battery_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Battery5);
              break;
            case 5:
              Battery_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Battery6);
              break;
            case 6:
              Battery_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Battery7);
              break;
            case 7:
              Battery_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Battery8);
              break;
            case 8:
              Battery_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Battery9);
              break;
            case 9:
              Battery_Adc[ADC_Buffer_Point] = ADC_Result;
              ADC_StartConversion(Battery10);
              break;
            case 10:
              Volt_Aquire = 0;
              Volt_Done = 1;
              break;
        }
        ADC_Buffer_Point++;
    }
}
/**
 End of File
*/