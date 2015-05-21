#include "CoolingControl.h"
#include "DigiPot.h"
#include "pwm.h"

void CoolingStart()
{
    PotSetpoint(pumpStart);
    PWMupdate(fanStart);
}

void CoolingUpdate(void)
{

}
