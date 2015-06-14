#include <xc.h>
#include "Define.h"
#include "Battery.h"
#include "Global.h"
#include "mcc_generated_files/adc.h"

float Battery_Volt[10]={3.000,3.000,3.000,3.000,3.000,3.000,3.000,3.000,3.000,3.000};
float TempBattery_Volt[10];
float PrevBattery_Volt[10];

/*******************************************************************
 * @brief           Battery_Read
 * @brief           sets ADC up for battery voltage read
 * @return          nothing
 * @note            it set's up the adc and uses ADC ISR to read all battery analog inputs
 *******************************************************************/

void Battery_Read() {
    //Set the ADC interupt to start to fill in the Battery ADC Buffer
    ADC_Buffer_Point = 0;
    Volt_Aquire = 1; //Set global flag for ADC ISR to trigger battery volt reads
    ADCON1 = 0x80; //Set up to run ADC from VDD to Vref- (2.5v) Put back to 0x81
    ADC_StartConversion(Battery1); //We need to get the ball rolling...
}

/*******************************************************************
 * @brief           Battery_Convert
 * @brief           takes battery cell ADC counts and converts to volts
 * @return          nothing
 * @note            this fcn needs to take account of the -vref (configgured by above fcn)
 *******************************************************************/

void Battery_Convert() {
    int x;
    for (x = 0; x <= NUMOFBATT; x++) {
        TempBattery_Volt[x] = ((Battery_Adc[x] / 1024.0)*5.0) + 0.05; //Normal converson w/ 2.5v offset (vref neg = 2.5v)
    }
    Battery_Filter();
}

/*******************************************************************
 * @brief           Battery_Filter
 * @brief           takes battery volts and does a exp. filter
 * @return          nothing
 * @note            May require adjustment (in define.h)
 *******************************************************************/

void Battery_Filter() {
    // This is a exponential moving average. 
    int x;
    for (x = 0; x <= NUMOFBATT; x++) {
        Battery_Volt[x] = TempBattery_Volt[x];// (BATALPHA * TempBattery_Volt[x] + ((1 - BATALPHA) * PrevBattery_Volt[x]));
    }
    for (x = 0; x <= NUMOFBATT; x++) {
        PrevBattery_Volt[x] = Battery_Volt[x];
    }
}

/*******************************************************************
 * @brief           Controls Fault
 * @brief           takes battery volts and determans over / under conditions
 * @return          returns 1 if over / under is met
 * @note            used for serial comm. 
 *******************************************************************/

char Battery_Fault() {
    char fault = 0; // Init fault as if there is none
    for (int i = 0; i <= NUMOFBATT; i++) {
        if ((BATLOW < Battery_Volt[i]) && (BATHIGH > Battery_Volt[i])) {
            fault = 1; // Set fault if found! Uh-Oh!!!!
        }
    }
    return fault;
}

/*******************************************************************
 * @brief           Battery_Get
 * @brief           used for testing / UART stuff
 * @param[in]       channelnum - what battery to return voltage of
 * @return          battery cell voltage 
 * @note            getter
 *******************************************************************/

float Battery_Get(int channelnum) {
    //return      TempBattery_Volt[channelnum];
    return Battery_Volt[channelnum];
}//



