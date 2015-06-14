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
        ToSend(BATTERY1V, Battery_Get(0)*1000);
        ToSend(BATTERY2V, Battery_Get(1)*1000);
        ToSend(BATTERY3V, Battery_Get(2)*1000);
        ToSend(BATTERY4V, Battery_Get(3)*1000);
        ToSend(BATTERY5V, Battery_Get(4)*1000);
        ToSend(BATTERY6V, Battery_Get(5)*1000);
        ToSend(BATTERY7V, Battery_Get(6)*1000);
        ToSend(BATTERY8V, Battery_Get(7)*1000);
        ToSend(BATTERY9V, Battery_Get(8)*1000);
        ToSend(BATTERY10V, Battery_Get(9)*1000);
        ToSend(BATTERY1T, Tempeture_Get(0));
        ToSend(BATTERY2T, Tempeture_Get(1));
        ToSend(BATTERY3T, Tempeture_Get(2));
        ToSend(BATTERY4T, Tempeture_Get(3));
        ToSend(BATTERY5T, Tempeture_Get(4));
        ToSend(BATTERY6T, Tempeture_Get(5));
        ToSend(BATTERY7T, Tempeture_Get(6));
        ToSend(BATTERY8T, Tempeture_Get(7));
        ToSend(BATTERY9T, Tempeture_Get(8));
        ToSend(BATTERY10T, Tempeture_Get(9));
        sendData(BMM_MASTER_ADDRESS);
        Delay(10);
        RS485 = 0;
        LATAbits.LATA4 ^= 1;
    }

}