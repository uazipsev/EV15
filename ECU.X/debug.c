#include "debug.h"
#include "ADDRESSING.h"
 void handleDebugRequests();
 void handleDebugRequests(){
     
     if(receiveData2()){
         ToSend2(RESPONSE_ADDRESS, ECU_ADDRESS);
         sendData2(DEBUG_ADDRESS);
     }
     
 }