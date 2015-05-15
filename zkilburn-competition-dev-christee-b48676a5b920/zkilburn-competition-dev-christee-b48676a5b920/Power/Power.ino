

#include <Math.h>
#include <Average.h>
#include <Timers.h>
#include <EEPROM.h>
#include <FastTransfer.h>
#include "power.h"
#include "PowerStructs.h"

void updateLED();
void updateSensorReading();
void initializeCommunicaton();
void updateDebug();
void updateCommunication();
void calculatePower();
void updateSensorReading();

void setup()
{
  pinMode(volts,INPUT);
  pinMode(amps,INPUT);
  pinMode(circuitVolts,INPUT);
  pinMode(circuitAmps,INPUT);
  initializeCommunicaton();
  delay(2000);
}


void loop()
{
  updateSensorReading();
  calculatePower();
  updateCommunication();
  //updateDebug();
  updateLED();
}




