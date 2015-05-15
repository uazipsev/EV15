#define acceptableGyroBeaconAngle           3
#define gyroCorrectBeaconCenterMinAngle     3
#define gyroCorrectBeaconCenterMaxAngle    35
#define ROBOT_ANGLE_CORRECT_WIDE           90
#define SERVO_MIN                          35
#define SERVO_MAX                         145

bool wiiCameraLocalize(int targetBeacon, int targetAngle, int cameraNumber)
{
  Navigation.ToSend(WII_SUBSYSTEM_MODE,3);
  Navigation.ToSend(3+cameraNumber,targetBeacon);
  Navigation.sendData(PIC_ADDRESS);
  bool doneLocalizing=false;
  int sweepCount=numberSweeps;
  static Timers decisionTimer(250);
  while(!doneLocalizing&&(macro_stop!=1))
  {
              sweepCount=numberSweeps;
                            
                      //while the wii camera doesnt see it..
                      while((macro_stop!=1)&&(!beaconSeen))
                      {
                        //if we have swept a number of times
                        if((numberSweeps>(sweepCount+2)))
                        {
                          static int turnCount;
                          //Reposition for another look                          
                          doTurn(ROBOT_ANGLE_CORRECT_WIDE);
                          turnCount++;
                          //if you have turned too much give up on this beacon...
                          if(turnCount> (540/ROBOT_ANGLE_CORRECT_WIDE))
                            return false;
                          //Wait some sweeps for recheck
                          sweepCount=numberSweeps;
                          delay(200);
                        }
                        //Listen for break and for wii
                        macroCommunicationsUpdate();        
                      }
                        
//                            //Allow to center -- do small adjustments if camera is on edge of capable angle
                            while(((macro_stop!=1)&&(beaconSeen[cameraNumber]))&&(!beaconCentered))
                            {
                              if(decisionTimer.timerDone())
                              {
                                if(beaconAngle[cameraNumber]<SERVO_MIN+10){
                                  doTurn(5);
                                }        
                                else if((beaconAngle[cameraNumber]>SERVO_MAX-10)){
                                  doTurn(-5);
                                }
                                decisionTimer.resetTimer();
                              }
                              //Listen for break and for wii
                              macroCommunicationsUpdate(); 
                            }


                            //Then make angle = what you want;
                            while( (!(((beaconAngle[cameraNumber]-acceptableGyroBeaconAngle)<targetAngle)&&((beaconAngle[cameraNumber]+acceptableGyroBeaconAngle)>targetAngle)))&&((macro_stop!=1)&&(beaconCentered))&&!doneLocalizing)
                            {
                              if(decisionTimer.timerDone())
                              {
                                if(beaconAngle[cameraNumber]<targetAngle)
                                {
                                  doTurn(constrain((targetAngle-beaconAngle[cameraNumber]),gyroCorrectBeaconCenterMinAngle,gyroCorrectBeaconCenterMaxAngle));         
                                }
                                else
                                {
                                  doTurn(constrain((targetAngle-beaconAngle[cameraNumber]),-gyroCorrectBeaconCenterMaxAngle,-gyroCorrectBeaconCenterMinAngle)); 
                                }
                                delay(105);
                                decisionTimer.resetTimer();
                              }
                              //Listen for break and for wii
                              macroCommunicationsUpdate(); 
                              
                              if(( ( (beaconAngle[cameraNumber]-acceptableGyroBeaconAngle) <targetAngle)&&((beaconAngle[cameraNumber]+acceptableGyroBeaconAngle)>targetAngle)))
                              {
                                doneLocalizing=true;
                                break;
                              }
                            }      
    
                            macroCommunicationsUpdate(); 
                          if(( ( (beaconAngle[cameraNumber]-acceptableGyroBeaconAngle) <targetAngle)&&((beaconAngle[cameraNumber]+acceptableGyroBeaconAngle)>targetAngle)))
                            {
                              doneLocalizing=true;
                              break;
                            }
  }

}


