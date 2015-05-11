#include "Shift595.h"
#include "mcc_generated_files/pin_manager.h"


void SetPin595(int Reg, int pin, int value)
{
   registers[((Reg-1)*8)+pin] = value;
}

void writeRegisters(){

  //CLK_SetLow();

  for(int i = numOfRegisterPins - 1; i >=  0; i--){
    //CLK_SetLow();

    int val = registers[i];
    if (val == HIGH )
    {
        DATA_OUT_SetHigh();
    }
    if (val == LOW )
    {
        DATA_OUT_SetLow();
    }
    //digitalWrite(SER_Pin, val);
    //CLK_SetHigh();

  }
  //digitalWrite(RCLK_Pin, HIGH);

}

