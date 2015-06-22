#include <stdbool.h>
#include "Communications.h"
#include "ADDRESSING.h"
#include <xc.h>
#include "SlaveAddressing.h"
#include "Battery.h"
#include "Tempeture.h"
#include "Global.h"
#define RS485 LATEbits.LATE1
extern void Delay(long int d_lenth);

void updateComms() {
    //        ToSend(RESPONSE_ADDRESS, THIS_ADDRESS);
    //        sendData(BMM_ADDRESS);
    if (receiveData()) {
        Delay(5);
        RS485 = 1;
        Delay(5);
        ToSend(RESPONSE_ADDRESS, THIS_ADDRESS);
        ToSend(BATTERY1V, (int) (Battery_Get(0)*1000.0));
        ToSend(BATTERY2V, (int) (Battery_Get(1)*1000.0));
        ToSend(BATTERY3V, (int) (Battery_Get(2)*1000.0));
        ToSend(BATTERY4V, (int) (Battery_Get(3)*1000.0));
        ToSend(BATTERY5V, (int) (Battery_Get(4)*1000.0));
        ToSend(BATTERY6V, (int) (Battery_Get(5)*1000.0));
        ToSend(BATTERY7V, (int) (Battery_Get(6)*1000.0));
        ToSend(BATTERY8V, (int) (Battery_Get(7)*1000.0));
        ToSend(BATTERY9V, (int) (Battery_Get(8)*1000.0));
        ToSend(BATTERY10V, (int) (Battery_Get(9)*1000.0));
        ToSend(BATTERY1T, (int) Tempeture_Get(0));
        ToSend(BATTERY2T, (int) Tempeture_Get(1));
        ToSend(BATTERY3T, (int) Tempeture_Get(2));
        ToSend(BATTERY4T, (int) Tempeture_Get(3));
        sendData(BMM_MASTER_ADDRESS);
        Delay(10);
        RS485 = 0;
        LATAbits.LATA4 ^= 1;
    }

}