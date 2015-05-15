//motor.ino
//created by Igor Vinograd

//Motor control board
#include <FastTransfer.h>
//#include <EasyTransferCRC.h>
#include <Servo.h>
#include <Timers.h>
#include "Variables.h"

#include "Methods.h"

#include "Structs.h"

//Communcications update method/fast transfer calls
#include "Comms.h"

//Motor controller output
#include "Servos.h"

//input systems (actuator/ )
#include "Pins.h"


void setup(){
  initializeLed();
  initializeCommunication();
  initializeServos();
}

void loop(){
  updateComms();
  updateServos();
  updateLed();
  updateOffset();
  updateAngle();
}


