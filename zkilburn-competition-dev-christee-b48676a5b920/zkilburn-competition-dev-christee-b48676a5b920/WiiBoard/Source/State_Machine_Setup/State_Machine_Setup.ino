// Example of using the PVision library for interaction with the Pixart sensor on a WiiMote
// This work was derived from Kako's excellent Japanese website
// http://www.kako.com/neta/2007-001/2007-001.html

// Steve Hobley 2009 - www.stephenhobley.com


const char irAddr = 0xB0 >> 1;

#include <Servo.h>
#include <Wire.h>  
#include <math.h>
#include <FastTransfer.h>
#include <PVision.h>
#include "Communications.h"

//WII FUNCTION DEFINES
#define VERTICAL 0
#define HORIZONTAL 1
#define BOTH 2
#define V_H_DISTANCE 20
#define acceptableCenterRangeOver2 125
#define INVALID 9999

//SERVO DEFINES
#define SLEWRATE_SERVO_RATE 75 //Adjustment from off centerd pixel to servo angle turn, for quicker adjustments than 1 degree
#define softSweepSpeedMax 3
#define wideSweepSpeedMax 10
#define MINANGLE_SERVO 0
#define MAXANGLE_SERVO 180

//DEBUG LEVEL DEFINES
#define debugLEVEL 0  

#define ONROBOT true
//Characterized found that center pixel is on range [-127,895] making it 895-511=384
const int CENTEREDPIXEL = 384; //450 280  //What appears to be an arbitrary pixel not represented by 1024 / 2 = 512

#define servoPin 3

//--------------------------WiiCamera Characteristics---------------------------------------

PVision ircam;            //Create a wii camera entity
char result;              //storage container for which blobs returned

int centerBeacon = INVALID; //Initial value for the location the center of the beacon is currently found
int detectedWidth = 0, detectedHeight = 0;

//---------------------NeoPixel Setup---------------------------------------
//#include <Adafruit_NeoPixel.h>
//#define PixelPin 7
//DEBUG strip - extra flashy and 4 long for 4 blobs is basic demo
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, PixelPin, NEO_GRB + NEO_KHZ800);

//-----------------------Servo Setup--------------------------------------------
Servo myservo;  // create servo object to control a servo
int pos = MINANGLE_SERVO;    // variable to store the servo position
#include "servoControls.h"


int numberSweeps;
bool rotatingLeft = false, rotatingRight = true; //Which direction are we turning(redudant variables for legibility)

void setup()
{
  myservo.attach(servoPin);  // attaches the servo on servoPin to the servo object

  //strip.begin(); //Turn on the neopixel library
  //strip.show(); // Initialize all pixels to 'off'
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600); //Start up the debug terminal system
  nav_receive[REQUESTEDBEACON] = HORIZONTAL;
  //ircam.init();      //boot wii camera
  //customParameters
  /*
   Level 1: p0 = 0x72, p1 = 0x20, p2 = 0x1F, p3 = 0x03
   Level 2: p0 = 0xC8, p1 = 0x36, p2 = 0x35, p3 = 0x03
   Level 3: p0 = 0xAA, p1 = 0x64, p2 = 0x63, p3 = 0x03
   Level 4: p0 = 0x96, p1 = 0xB4, p2 = 0xB3, p3 = 0x04
   Level 5: p0 = 0x96, p1 = 0xFE, p2 = 0xFE, p3 = 0x05

   Quoting the Wiimote Wiki IR sensor page, these parameters correspond to:
   p0: MAXSIZE: Maximum blob size. Wii uses values from 0x62 to 0xc8
   p1: GAIN: Sensor Gain. Smaller values = higher gain
   p2: GAINLIMIT: Sensor Gain Limit. Must be less than GAIN for camera to function. No other effect?
   p3: MINSIZE: Minimum blob size. Wii uses values from 3 to 5
   */
  ircam.init(0xFE, 0xB4, 0xB3, 0x03);
  delay(100);
  navigationComm.begin(Details(nav_receive), 9, false, &Serial);
  navigationComm.ToSend(DISTANCE_FROM_CENTER, INVALID);
  navigationComm.ToSend(BEACON_ANGLE, INVALID);
  navigationComm.ToSend(NUMBER_SWEEPS, 0);
  navigationComm.ToSend(BEACON_SEEN, 0);
  navigationComm.ToSend(BEACON_CENTERED, 0);
  navigationComm.ToSend(TARGET_BEACON, nav_receive[REQUESTEDBEACON]);
  if (ONROBOT) navigationComm.sendData(NAV_Address);
}



void loop()
{
  while (!isAbout(centerBeacon, CENTEREDPIXEL, acceptableCenterRangeOver2))
  {
    //Receive Packet from Navigation
    navigationComm.receiveData();
    //Make angle 90 for quick check
    while (nav_receive[REQUESTEDBEACON] == 90)
    {
      myservo.write(90);
      navigationComm.receiveData();
      delay(50);
    }
    
    //Update Camera Information
    result = ircam.read();
    if(!ONROBOT) debugBlobs();
    updateCenterBeacon();
    
    //If beacon is not there
    if (centerBeacon == INVALID)
    { 
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      navigationComm.ToSend(DISTANCE_FROM_CENTER, INVALID);
      navigationComm.ToSend(BEACON_ANGLE, INVALID);
      navigationComm.ToSend(BEACON_SEEN, 0);
      navigationComm.ToSend(BEACON_CENTERED, 0);
      navigationComm.ToSend(TARGET_BEACON, nav_receive[REQUESTEDBEACON]);
      //FUNCTION
      sweepLook();
    
    }
    //else if beacon is there and is on left side of picture
    else if (centerBeacon < CENTEREDPIXEL)
    {
      digitalWrite(6, LOW);
      digitalWrite(7, HIGH);
      navigationComm.ToSend(DISTANCE_FROM_CENTER, CENTEREDPIXEL - centerBeacon);
      navigationComm.ToSend(BEACON_ANGLE, pos);
      navigationComm.ToSend(BEACON_SEEN, 1);
      navigationComm.ToSend(BEACON_CENTERED, 0);
      navigationComm.ToSend(TARGET_BEACON, nav_receive[REQUESTEDBEACON]);
      
      //FUNCTION FINE SWEEP
      rotateRight(constrain(((abs(CENTEREDPIXEL - centerBeacon)) / SLEWRATE_SERVO_RATE), 1, softSweepSpeedMax));
      rotatingLeft = false;
      rotatingRight = true;
      
      delay(125);
    }    
    //else if beacon is there and is on right side of picture
    else if (centerBeacon > CENTEREDPIXEL)
    {
      digitalWrite(6, LOW);
      digitalWrite(7, HIGH);
      navigationComm.ToSend(DISTANCE_FROM_CENTER, CENTEREDPIXEL - centerBeacon);
      navigationComm.ToSend(BEACON_ANGLE, pos);
      navigationComm.ToSend(BEACON_SEEN, 1);
      navigationComm.ToSend(BEACON_CENTERED, 0);
      navigationComm.ToSend(TARGET_BEACON, nav_receive[REQUESTEDBEACON]);
      
      //FUNCTION FINE SWEEP
      rotateLeft(constrain(((abs(CENTEREDPIXEL - centerBeacon)) / SLEWRATE_SERVO_RATE), 1, softSweepSpeedMax));
      rotatingLeft = true;
      rotatingRight = false;
      
      delay(125);
    }
    navigationComm.ToSend(BEACON_WIDTH, detectedWidth);
    //Send data if we are not doing testing
    if (ONROBOT) navigationComm.sendData(NAV_Address);
    
    delay(105);
  }
  
  
  //  Serial.print("\n\nFound the LED Beacon at angle: ");
  //  Serial.println(pos);
  //  Serial.print("Detected Width: ");
  //  Serial.println(detectedWidth);
  
  navigationComm.ToSend(BEACON_ANGLE, pos);
  navigationComm.ToSend(BEACON_SEEN, 1);
  navigationComm.ToSend(BEACON_CENTERED, 1);
  navigationComm.ToSend(BEACON_WIDTH, detectedWidth);
  navigationComm.ToSend(TARGET_BEACON, nav_receive[REQUESTEDBEACON]);  
  if (ONROBOT)  navigationComm.sendData(NAV_Address);

  //While the beacon is centered within a margin of error
  while (isAbout(centerBeacon, CENTEREDPIXEL, acceptableCenterRangeOver2 + 20))
  {    
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);    
    navigationComm.ToSend(BEACON_ANGLE, pos);
    navigationComm.ToSend(BEACON_SEEN, 1);
    navigationComm.ToSend(BEACON_CENTERED, 1);
    navigationComm.ToSend(BEACON_WIDTH, detectedWidth);
    navigationComm.ToSend(TARGET_BEACON, nav_receive[REQUESTEDBEACON]);
    if (ONROBOT)  navigationComm.sendData(NAV_Address);
    
    result = ircam.read();
    
    if(!ONROBOT) debugBlobs();
    updateCenterBeacon();
    navigationComm.receiveData();
    
    //If beacon is locked on at 90 degrees
    if (isAbout(pos, 90, 3))
    {
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
    }
    
    delay(200);
    
    //Prepare to turn away from the beacon your looking at
    if (nav_receive[REQUESTEDBEACON] == VERTICAL)
    {
      rotatingLeft = true;
      rotatingRight = false;
    }
    else if (nav_receive[REQUESTEDBEACON] == HORIZONTAL)
    {

      rotatingLeft = false;
      rotatingRight = true;
    }
    
    if (!ONROBOT)
    {
      if (nav_receive[REQUESTEDBEACON] == VERTICAL)
      {
        nav_receive[REQUESTEDBEACON] = HORIZONTAL;
        updateCenterBeacon();
        if (debugLEVEL == 1)
        {
          Serial.print("Found the vertical beacon at: ");
          Serial.println(pos);
        }
        rotatingLeft = false;
        rotatingRight = true;
        delay(1000);
      }
      else   if (nav_receive[REQUESTEDBEACON] == HORIZONTAL)
      {
        nav_receive[REQUESTEDBEACON] = VERTICAL;
        updateCenterBeacon();
        if (debugLEVEL == 1)
        {
          Serial.print("Found the horizontal beacon at: ");
          Serial.println(pos);
        }
        rotatingLeft = true;
        rotatingRight = false;
        delay(1000);
      }
    }
  } 
    result = ircam.read();
    if(!ONROBOT) debugBlobs();
    updateCenterBeacon();
  if (ONROBOT)  navigationComm.sendData(NAV_Address);
}

void prepData()
{
  navigationComm.ToSend(DISTANCE_FROM_CENTER, INVALID);
  navigationComm.ToSend(BEACON_ANGLE, INVALID);
  navigationComm.ToSend(BEACON_SEEN, 0);
  navigationComm.ToSend(BEACON_CENTERED, 0);
  navigationComm.ToSend(BEACON_WIDTH, detectedWidth);
  navigationComm.ToSend(TARGET_BEACON, nav_receive[REQUESTEDBEACON]);
}

void resetSystem() {
  //strip.setPixelColor(0, strip.Color(255, 0, 0));
  //strip.show();
  Serial.print("Found the LED Beacon at angle: ");
  Serial.println(pos);
  delay(1000);
  myservo.write(0);
  pos = 0;
  centerBeacon = INVALID;
  //colorWipe(strip.Color(0, 0, 0), 4); //Wipe

}



void sweepLook(){
    if ((pos < MAXANGLE_SERVO) && rotatingRight)
      {
        rotateRight(wideSweepSpeedMax);
        delay(105);
      }
      else if ((pos > MINANGLE_SERVO) && rotatingLeft)
      {
        rotateLeft(wideSweepSpeedMax);
        delay(105);
      }
      else if (pos <= MINANGLE_SERVO)
      {
        navigationComm.ToSend(NUMBER_SWEEPS, numberSweeps++);
        rotatingLeft = false;
        rotatingRight = true;
      }
      else if (pos >= MAXANGLE_SERVO)
      {
        navigationComm.ToSend(NUMBER_SWEEPS, numberSweeps++);
        rotatingLeft = true;
        rotatingRight = false;
      }
}


bool isAbout(int compareThis, int value, int range)
{
  return ( ((compareThis - range) < value) && ((compareThis + range) > value));
}


  int minHeight=999,minWidth=999;
void updateCenterBeacon()
{

  //  int minX = 1500, maxX = 0;
  //  int minBlob = 0, maxBlob = 0;
  //  if (result & BLOB1)
  //  {
  //    if (ircam.Blob1.X < minX)
  //    {
  //      minX = ircam.Blob1.X;
  //      minBlob = 1;
  //    }
  //    if (ircam.Blob1.X > maxX)
  //    {
  //      maxX = ircam.Blob1.X;
  //      maxBlob = 1;
  //    }
  //
  //  }
  //  if (result & BLOB2)
  //  {
  //    if (ircam.Blob2.X < minX)
  //    {
  //      minX = ircam.Blob2.X;
  //      minBlob = 2;
  //    }
  //    if (ircam.Blob2.X > maxX)
  //    {
  //      maxX = ircam.Blob2.X;
  //      maxBlob = 2;
  //    }
  //  }
  //  if (result & BLOB3)
  //  {
  //    if (ircam.Blob3.X < minX)
  //    {
  //      minX = ircam.Blob3.X;
  //      minBlob = 3;
  //    }
  //    if (ircam.Blob3.X > maxX)
  //    {
  //      maxX = ircam.Blob3.X;
  //      maxBlob = 3;
  //    }
  //  }
  //  if (result & BLOB4)
  //  {
  //    if (ircam.Blob4.X < minX)
  //    {
  //      minX = ircam.Blob4.X;
  //      minBlob = 4;
  //    }
  //    if (ircam.Blob2.X > maxX)
  //    {
  //      maxX = ircam.Blob4.X;
  //      maxBlob = 4;
  //    }
  //  }
  int vertical[3], horizontal[3];
  minHeight=999;
  minWidth=999;
  for (int i = 0; i < 3; i++)
  {
    vertical[i] = INVALID;
    horizontal[i] = INVALID;
  }
  int center = INVALID;

  if     ((result & BLOB1) && (result & BLOB2))
  {
    detectedWidth = abs(ircam.Blob1.X - ircam.Blob2.X);
    detectedHeight = abs(ircam.Blob1.Y - ircam.Blob2.Y);
    center = (ircam.Blob1.X + ircam.Blob2.X) / 2;
    if ((detectedWidth < V_H_DISTANCE) && (detectedWidth<minWidth))
    {
      minWidth=detectedWidth;
      vertical[0] = 1;
      vertical[1] = 2;
      center = (ircam.Blob1.X + ircam.Blob2.X) / 2;
      vertical[2]= center;
      
    }
    if ((abs(detectedHeight) < V_H_DISTANCE) && (abs(detectedHeight)<minHeight))
    {
      minHeight=abs(detectedHeight);
      horizontal[0] = 1;
      horizontal[1] = 2;
      center = (ircam.Blob1.X + ircam.Blob2.X) / 2;
      horizontal[2]= center;
    }
    if (nav_receive[REQUESTEDBEACON] == BOTH)
    {
      center = (ircam.Blob1.X + ircam.Blob2.X) / 2;
    }
  }
   if ((result & BLOB1) && (result & BLOB3))
  {
    detectedWidth = abs(ircam.Blob1.X - ircam.Blob3.X);
    detectedHeight = abs(ircam.Blob1.Y - ircam.Blob3.Y);
    center = (ircam.Blob1.X + ircam.Blob3.X) / 2;
    if ((detectedWidth < V_H_DISTANCE) && (detectedWidth<minWidth))
    {
      minWidth=detectedWidth;
      vertical[0] = 1;
      vertical[1] = 3;
      center = (ircam.Blob1.X + ircam.Blob3.X) / 2;
      vertical[2]= center;
    }
    if ((abs(detectedHeight) < V_H_DISTANCE) && (abs(detectedHeight)<minHeight))
    {
      minHeight=abs(detectedHeight);
      horizontal[0] = 1;
      horizontal[1] = 3;
      center = (ircam.Blob1.X + ircam.Blob3.X) / 2;
      horizontal[2]= center;
    }
    if (nav_receive[REQUESTEDBEACON] == BOTH)
    {
      center = (ircam.Blob1.X + ircam.Blob3.X) / 2;
    }
  }
   if ((result & BLOB1) && (result & BLOB4))
  {
    detectedWidth = abs(ircam.Blob1.X - ircam.Blob4.X);
    detectedHeight = abs(ircam.Blob1.Y - ircam.Blob4.Y);
     if ((detectedWidth < V_H_DISTANCE) && (detectedWidth<minWidth))
    {
      minWidth=detectedWidth;
      vertical[0] = 1;
      vertical[1] = 4;
      center = (ircam.Blob1.X + ircam.Blob4.X) / 2;
      vertical[2]= center;
    }
    if ((abs(detectedHeight) < V_H_DISTANCE) && (abs(detectedHeight)<minHeight))
    {
      minHeight=abs(detectedHeight);
      horizontal[0] = 1;
      horizontal[1] = 4;
      center = (ircam.Blob1.X + ircam.Blob4.X) / 2;
      horizontal[2]= center;
    }
    if (nav_receive[REQUESTEDBEACON] == BOTH)
    {
      center = (ircam.Blob1.X + ircam.Blob4.X) / 2;
    }
  }
   if ((result & BLOB2) && (result & BLOB3))
  {
    detectedWidth = abs(ircam.Blob2.X - ircam.Blob3.X);
    detectedHeight = abs(ircam.Blob2.Y - ircam.Blob3.Y);
    if ((detectedWidth < V_H_DISTANCE) && (detectedWidth<minWidth))
    {
      minWidth=detectedWidth;
      vertical[0] = 2;
      vertical[1] = 3;
      center = (ircam.Blob2.X + ircam.Blob3.X) / 2;
      vertical[2]= center;
    }
    if ((abs(detectedHeight) < V_H_DISTANCE) && (abs(detectedHeight)<minHeight))
    {
      minHeight=abs(detectedHeight);
      horizontal[0] = 2;
      horizontal[1] = 3;
      center = (ircam.Blob2.X + ircam.Blob3.X) / 2;
      horizontal[2]= center;
    }
    if (nav_receive[REQUESTEDBEACON] == BOTH)
    {
      center = (ircam.Blob2.X + ircam.Blob3.X) / 2;
    }
  }
   if ((result & BLOB2) && (result & BLOB4))
  {
    detectedWidth = abs(ircam.Blob2.X - ircam.Blob4.X);
    detectedHeight = abs(ircam.Blob2.Y - ircam.Blob4.Y);
    if ((detectedWidth < V_H_DISTANCE) && (detectedWidth<minWidth))
    {
      minWidth=detectedWidth;
      vertical[0] = 2;
      vertical[1] = 4;
      center = (ircam.Blob2.X + ircam.Blob4.X) / 2;
      vertical[2]= center;
    }
    if ((abs(detectedHeight) < V_H_DISTANCE) && (abs(detectedHeight)<minHeight))
    {
      minHeight=abs(detectedHeight);
      horizontal[0] = 2;
      horizontal[1] = 4;
      center = (ircam.Blob2.X + ircam.Blob4.X) / 2;
      horizontal[2]= center;
    }
    if (nav_receive[REQUESTEDBEACON] == BOTH)
    {
      center = (ircam.Blob2.X + ircam.Blob4.X) / 2;
    }
  }
   if ((result & BLOB3) && (result & BLOB4))
  {
    detectedWidth = abs(ircam.Blob3.X - ircam.Blob4.X);
    detectedHeight = abs(ircam.Blob3.Y - ircam.Blob4.Y);
    if ((detectedWidth < V_H_DISTANCE) && (detectedWidth<minWidth))
    {
      minWidth=detectedWidth;
      vertical[0] = 3;
      vertical[1] = 4;
      center = (ircam.Blob3.X + ircam.Blob4.X) / 2;
      vertical[2]= center;
    }
     if ((abs(detectedHeight) < V_H_DISTANCE) && (abs(detectedHeight)<minHeight))
    {
      minHeight=abs(detectedHeight);
      horizontal[0] = 3;
      horizontal[1] = 4;
      center = (ircam.Blob3.X + ircam.Blob4.X) / 2;
      horizontal[2]= center;
    }
    if (nav_receive[REQUESTEDBEACON] == BOTH)
    {
      center = (ircam.Blob3.X + ircam.Blob4.X) / 2;
    }
  }
  else
  {
    detectedHeight = 0;
    detectedWidth = 0;
    center = INVALID;
  }
  debugBlobs();


  if (nav_receive[REQUESTEDBEACON] == VERTICAL)
  {
    if ((vertical[2] != INVALID))
    {
      centerBeacon = vertical[2];
    }
    else
    {
      centerBeacon = INVALID;
    }
  }
  else if (nav_receive[REQUESTEDBEACON] == HORIZONTAL)
  {
    if ((horizontal[2] != INVALID))
    {
      centerBeacon = horizontal[2];
    }
    else
    {
      centerBeacon = INVALID;
    }
  }
  else if (nav_receive[REQUESTEDBEACON] == BOTH)
  {
    if ((center != INVALID))
    {
      centerBeacon = center;
    }
    else
    {
      centerBeacon = INVALID;
    }
  }
  else
  {
    centerBeacon = INVALID;
  }

  return;
}

void debugBlobs()
{
  if (!ONROBOT) {
    if (debugLEVEL == 1)
    {
      //Serial.println("");
      Serial.print("  DetectedWidth: ");
      Serial.print(minWidth);
      Serial.print("  DetectedHeight: ");
      Serial.print(minHeight);
      Serial.print("  CenterPixelOfBeacon:: ");
      Serial.print(centerBeacon);
      Serial.print("  Servo Angle:");
      Serial.print(pos);
      if (result & BLOB1)
      {
        Serial.print("  BLOB1 detected. X:");
        Serial.print(ircam.Blob1.X);
        Serial.print(" Y:");
        Serial.print(ircam.Blob1.Y);
        Serial.print(" Size:");
        Serial.print(ircam.Blob1.Size);
      }

      if (result & BLOB2)
      {
        Serial.print("  BLOB2 detected. X:");
        Serial.print(ircam.Blob2.X);
        Serial.print(" Y:");
        Serial.print(ircam.Blob2.Y);
        Serial.print(" Size:");
        Serial.print(ircam.Blob2.Size);
      }
      if (result & BLOB3)
      {
        Serial.print("  BLOB3 detected. X:");
        Serial.print(ircam.Blob3.X);
        Serial.print(" Y:");
        Serial.print(ircam.Blob3.Y);
        Serial.print(" Size:");
        Serial.print(ircam.Blob3.Size);
      }
      if (result & BLOB4)
      {
        Serial.print("  BLOB4 detected. X:");
        Serial.print(ircam.Blob4.X);
        Serial.print(" Y:");
        Serial.print(ircam.Blob4.Y);
        Serial.print(" Size:");
        Serial.print(ircam.Blob4.Size);
      }
      Serial.println(" ");
    }
  }
  else if (debugLEVEL == 2)
  {

  }
}
// Fill the dots one after the other with a color
//void colorWipe(uint32_t c, uint8_t wait) {
//  for(uint16_t i=0; i<strip.numPixels(); i++) {
//    strip.setPixelColor(i, c);
//    strip.show();
//    delay(wait);
//  }
//}








