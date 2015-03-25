#include "Define.h"
#include "Battery.h"

bool Battery_Fault()
{
    // Init fault as if there is none
    bool fault = 0;
    for(int i = 0;i<9;i++)
    {
        if ((BATLOW < Battery[i]) && (BATHIGH > Battery[i]))
        {
            fault = 1;
        }
    }

    return fault;
}