
//communications.ino

//Version 19
//created by zac kilburn and igor vinograd
//2/15/14

// initialize the needed libraries
#include <FastTransfer.h>
#include <EasyTransfer.h>
#include <EasyTransferCRC.h>
#include <digitalWriteFast.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Average.h>
#include <PID.h>
#include <Timers.h>

// include the .h files
#include "Definitions.h"
#include "Variables.h"
#include "Structs.h"
#include "Methods.h"
#include "Debug.h"
#include "macroStateHandler.h"
#include "Comms.h"

void setup() {
  pinMode(13, OUTPUT);
  initializeCommunications();
  selectCommLines(LEDcomm);
}

void loop() {
  updateComms();
 // updateDebug();
}



