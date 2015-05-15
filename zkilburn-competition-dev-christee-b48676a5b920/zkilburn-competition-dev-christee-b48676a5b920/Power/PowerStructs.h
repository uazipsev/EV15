
#define START_ADDRESS_EEPROM 0

Timers sender(125);

FastTransfer powerBoardComm;

#define LED 13

int receivedData[5];


//ADDRESSING FOR ROBOT
#define CONTROL_ADDRESS            5
#define NAVIGATION_ADDRESS         4
#define PIC_ADDRESS                1
#define MOTOR_ADDRESS              6
#define LED_ADDRESS                2
#define POWER_ADDRESS	           3

//RECEIEVED DATA
#define WIPE_DATA 1

//Send data
#define VOLTS         7
#define MILLIAMPS     8
#define MILLIAMPHOURS 9
#define WATTHOURS     10


void writePowerToEEPROM();
void recoverEEPROM();
void wipeEEPROM();

void initializeCommunicaton()
{
  pinMode(LED, OUTPUT);
  Serial.begin(57600);
  powerBoardComm.begin(Details(receivedData), POWER_ADDRESS, false, &Serial);
  recoverEEPROM();
}
void wipeEEPROM(){
  EEPROM.write(0,0); 
}
//run this at boot
void recoverEEPROM(){
   milliAmphours= EEPROM.read(0); 
}
//Run this every second
void writePowerToEEPROM()
{
    EEPROM.write(0,milliAmphours);
}

void updateDebug()
{
  static Timers debugTimer(25);
  if(debugTimer.timerDone())
  {  
    Serial.print("Raw: ");
    Serial.print((analogRead(amps)));     
    Serial.print(" MilliAmps: ");
    Serial.print(milliAmps);
    Serial.print(" Voltage: ");
    Serial.println((analogRead(amps) * (5000 / 1024)) - OFFSET_AMPS);    
//    Serial.println("");
//    Serial.println("");
//    Serial.print("MilliAmps: ");
//    Serial.println(milliAmps);
//    Serial.print("milliAmpHours: ");
//    Serial.println(milliAmphours);
//    Serial.print("Voltage: ");
//    Serial.println(circuitVoltage);
//    Serial.print("wattHours: ");
//    Serial.println(wattHours);  
  }

}

void updateCommunication()
{  
  
  powerBoardComm.receiveData();
  if(receivedData[WIPE_DATA]){
    receivedData[WIPE_DATA]=0;
    wipeEEPROM();
  }
  //if you recieve a packet from comm, send comm
 sender.updateTimer();
  if(sender.timerDone())
  {
    
    powerBoardComm.ToSend(MILLIAMPS,     milliAmps);
    powerBoardComm.ToSend(MILLIAMPHOURS, milliAmphours);
    powerBoardComm.ToSend(VOLTS,         voltage);
    powerBoardComm.ToSend(WATTHOURS,     wattHours);
    powerBoardComm.sendData(CONTROL_ADDRESS);
  }  
}

