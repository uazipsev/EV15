#include "Shift595.h"
#include "mcc_generated_files/pin_manager.h"
#include "xc.h"
#include "Functions.h"


void StartUp595()
{
    //Shut off outputs to get ready for config!
    OUTEN_SetHigh();
    //clear all shift reg's
    Delay(10);
    CLEAR_SetHigh();
    Delay(10);
    CLEAR_SetLow();
    Delay(10);
    CLEAR_SetHigh();
    Delay(10);
    //Init Config Done! Set for regular updates
    OUTEN_SetLow();
}

void SetPin595(int Reg, int pin, int value)
{
   registers[((Reg-1)*8)+pin] = value;
}

void Clear595()
{
  for(int i = RegPins - 1; i >=  0; i--){
     registers[i] = LOW;
  }
  writeRegisters();
}

void writeRegisters(){

  LAT_SetLow();

  for(int i = RegPins - 1; i >=  0; i--){
    CLK_SetLow();

    int val = registers[i];
    if (val == HIGH )
    {
        DATA_OUT_SetHigh();
    }
    if (val == LOW )
    {
        DATA_OUT_SetLow();
    }
    CLK_SetHigh();

  }
  LAT_SetHigh();

}

