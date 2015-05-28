
#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "Functions.h"
#include "PinDef.h"

#include "ADDRESSING.h"


int main(void)
{
    Setup();
    LED  = 0;
  
    while (1)
    {  
        static int sender;
        ToSend(THROTTLE1  , sender++);
//        ToSend(THROTTLE2  , sender++);
//        ToSend(BRAKE      , sender++);
//        ToSend(WHEELSPEED1, sender++);
//        ToSend(WHEELSPEED2, sender++);
//        ToSend(WHEELSPEED3, sender++);
//        ToSend(WHEELSPEED4, sender++);
        sendData(ECU_ADDRESS);
        Delay(500);
        LED  ^= 1;
    }
}
