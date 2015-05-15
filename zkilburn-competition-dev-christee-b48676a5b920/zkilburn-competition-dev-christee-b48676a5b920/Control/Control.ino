
//control.ino
//
//Version 19
//Created by Zac Kilburn with guidence from Igor Vinograd :)
//3/7/14


//Software Packages Include
#include <FastTransfer.h>
#include <Timers.h>
#include "SoftwareSerial.h"
#include "digitalWriteFast.h"
#include "Adafruit_Thermal.h"
#include <avr/pgmspace.h>

//Internal File Includes
#include "Methods.h"
#include "Definitions.h"
#include "Variables.h"
#include "Printer.h"
#include "Comms.h"
#include "Screen_Outgoing.h"
#include "Screen.h"
#include "MacroControl.h"
#include "PinMap.h"
#include "Debug.h"



void setup()
{
//  printerPrint();
//  while(1) ;
  delay(2500);
  initializeCommunicaton();
  initializePins();
  //writeContrast(15);
  activePage = 0;
  delay(2500);
  
  writeObject(FORMMESSAGE, 0, 1);

}

void loop() {
  controlsUpdate();
  macroUpdate();
  updateCommunication();
  updateScreen();
  updateDebug();
  ledUpdate();

}




