#include "Shift595.h"
#include "mcc_generated_files/pin_manager.h"
#include "xc.h"
#include "Functions.h"

/*
 * On init we want to clear out the shift Reg.
 * This code does that.
 */
void StartUp595()
{
    //Shut off outputs to get ready for config!
    OUTEN_SetHigh();
    //clear all shift reg's
    Delay(1);
    CLEAR_SetHigh();
    Delay(1);
    CLEAR_SetLow();
    Delay(1);
    CLEAR_SetHigh();
    Delay(1);
    //Init Config Done! Set for regular updates
    OUTEN_SetLow();
    Clear595();
}

/*
 * This piece of code allows use to set bits in the right paces to set outputs of the shift reg's
 * The fcn can't augment the array so you need to make sure the array is big enugh for the application
 */
void SetPin595(int Reg, int pin, int value)
{
   registers[((Reg-1)*8)+pin] = value;
}

/*
 *  This will clear the aray and set all outputs to zero
 */
void Clear595()
{
  for(int i = RegPins - 1; i >=  0; i--){
     registers[i] = LOW;
  }
  writeRegisters();
}

/*
 *  This is a fcn that will set outputs based the private array of this c file
 */
void writeRegisters(){

  LAT_SetLow();  // set select low

  for(int i = RegPins - 1; i >=  0; i--){
    CLK_SetLow();   //Set clock low (data is shifted in on rising edge)

    int val = registers[i];
    if (val == HIGH )
    {
        DATA_OUT_SetHigh();
    }
    if (val == LOW )
    {
        DATA_OUT_SetLow();
    }
    CLK_SetHigh();  //shift data in

  }
  LAT_SetHigh();  //Set latch high puting sent data to output

}

