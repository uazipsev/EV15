

#include <xc.h>
#include "adc.h"
#include "../Global.h"


/**
  Section: ADC Module APIs
*/

void ADC_Initialize(void)
{
    // set the ADC to the options selected in the User Interface
    
    // GO_nDONE stop; ADON enabled; CHS AN0; 
    ADCON0 = 0x01;
    
    // PVCFG VDD; TRIGSEL CTMU; NVCFG external; 
    ADCON1 = 0x81;
    
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
        Battery_Adc[ADC_Buffer_Point] = ADC_Result;
        ADC_Buffer_Point++;
        switch ( ADC_Buffer_Point )
        {
            case 1:
              ADC_StartConversion(Battery2);
              break;
            case 2:
              ADC_StartConversion(Battery3);
              break;
            case 3:
              ADC_StartConversion(Battery4);
              break;
            case 4:
              ADC_StartConversion(Battery5);
              break;
            case 5:
              ADC_StartConversion(Battery6);
              break;
            case 6:
              ADC_StartConversion(Battery7);
              break;
            case 7:
              ADC_StartConversion(Battery8);
              break;
            case 8:
              ADC_StartConversion(Battery9);
              break;
            case 9:
              Temp_Aquire = 0;
              ADC_StartConversion(Battery10);
              break;
        }
    }
    if (Volt_Aquire){
        //Do the Batt sensor ADC

        ADC_Result = ADC_GetConversionResult();
        Battery_Adc[ADC_Buffer_Point] = ADC_Result;
        ADC_Buffer_Point++;
        switch ( ADC_Buffer_Point )
        {
            case 1:
              ADC_StartConversion(Battery2);
              break;
            case 2:
              ADC_StartConversion(Battery3);
              break;
            case 3:
              ADC_StartConversion(Battery4);
              break;
            case 4:
              ADC_StartConversion(Battery5);
              break;
            case 5:
              ADC_StartConversion(Battery6);
              break;
            case 6:
              ADC_StartConversion(Battery7);
              break;
            case 7:
              ADC_StartConversion(Battery8);
              break;
            case 8:
              ADC_StartConversion(Battery9);
              break;
            case 9:
              Volt_Aquire = 0;
              ADC_StartConversion(Battery10);
              break;
        }
    }
}
/**
 End of File
*/