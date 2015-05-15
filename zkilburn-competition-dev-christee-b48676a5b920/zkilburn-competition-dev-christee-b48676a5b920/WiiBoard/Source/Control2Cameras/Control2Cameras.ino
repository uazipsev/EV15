#include <FastTransfer.h>
#include <math.h>
FastTransfer leftCamera, rightCamera;
int leftReceive[10], rightReceive[10];
#define INPUT_90_PIN A13

#define NAV_Address 1

#define DISTANCE_FROM_CENTER 1
#define BEACON_ANGLE 2
#define NUMBER_SWEEPS 3
#define BEACON_SEEN 4
#define BEACON_CENTERED 5
#define BEACON_WIDTH 6
#define TARGET_BEACON 7


#define REQUESTEDBEACON 1

float a[3], b[3];
float c1, c2, d, e, f, g, h;
float V, H;
float L = 100.0, K = 50.0, J = 39.0;
bool collected[6] = {false, false, false, false , false , false};
int requestBeaconNumber = 0;
void setup() {
  pinMode(INPUT_90_PIN,INPUT);
  Serial.begin(9600); //Debug
  Serial1.begin(9600); //Left Beacon (through Lantronix port)
  Serial2.begin(9600); //Right Beacon (through BT header JP1)
  leftCamera.begin(Details(leftReceive), NAV_Address, false, &Serial1);
  rightCamera.begin(Details(rightReceive), NAV_Address, false, &Serial2);

}
void loop() {
  while (1)
  {
  while(digitalRead(INPUT_90_PIN)){
         leftCamera.ToSend(REQUESTEDBEACON, 90);
        rightCamera.ToSend(REQUESTEDBEACON, 90);
      leftCamera.sendData(9);
      rightCamera.sendData(9);
  }
    delay(100);
    if (!collected[0] || !collected[1])
    {
      requestBeaconNumber = 0;
      leftCamera.ToSend(REQUESTEDBEACON, requestBeaconNumber);
      rightCamera.ToSend(REQUESTEDBEACON, requestBeaconNumber);
      leftCamera.sendData(9);
      rightCamera.sendData(9);
      Serial.println("Collecting Left Beacon");


    }
    else if (!collected[2] || !collected[3])
    {
      requestBeaconNumber = 1;
      leftCamera.ToSend(REQUESTEDBEACON, requestBeaconNumber);
      rightCamera.ToSend(REQUESTEDBEACON, requestBeaconNumber);
      leftCamera.sendData(9);
      rightCamera.sendData(9);

      Serial.println("Collecting Right Beacon");
    }
    else
    {
      for (int i = 0; i < 6; i++)
        collected[i] = false;     
      break;
    }
    
    leftCamera.ToSend(REQUESTEDBEACON, requestBeaconNumber);
    rightCamera.ToSend(REQUESTEDBEACON, requestBeaconNumber);
    leftCamera.sendData(9);
    rightCamera.sendData(9);
    delay(250);

    while (leftCamera.receiveData())
    {
      if (leftReceive[BEACON_CENTERED] != 0)
      {
        if(leftReceive[TARGET_BEACON]==requestBeaconNumber)
        {
        a[requestBeaconNumber] = leftReceive[BEACON_ANGLE];
        collected[requestBeaconNumber * 2] = true;        
        //       Serial.print("Left angle: ");
        //       Serial.println(leftReceive[BEACON_ANGLE]);
        }
      }
      else
      if(leftReceive[TARGET_BEACON]==requestBeaconNumber)
        {
        collected[requestBeaconNumber * 2] = false;
        }
    }
    while (rightCamera.receiveData())
    {
      if (rightReceive[BEACON_CENTERED] != 0)
      {
        if(rightReceive[TARGET_BEACON]==requestBeaconNumber)
        {
        b[requestBeaconNumber] = rightReceive[BEACON_ANGLE];
        collected[requestBeaconNumber * 2 + 1] = true;
        //       Serial.print("Right angle: ");
        //       Serial.println(rightReceive[BEACON_ANGLE]);
        }
      }
      else
        if(rightReceive[TARGET_BEACON]==requestBeaconNumber)
        {
        collected[requestBeaconNumber * 2 + 1] = false;
        }
    }
  }

  c1 = constrain(a[0] - b[0], 1, 179);
  c2 = constrain(a[1] - b[1], 1, 179);
  d = a[0] - (c1 / 2.0);
  e = 180 - b[1] - (c2 / 2.0);
  f = constrain(180 - d - e,1,179);
  H = (sin(180 - a[0]) * (J / 2.0)) / (sin(c1 / 2.0));
  V = (sin(b[1]) * (J / 2.0)) / (sin(c2 / 2.0));
  h = asin((V * sin(f)) / 50.0);
  g = constrain(180 - h - f,1,179);
  
  Serial.println();
  Serial.println();
  Serial.print("a[0]: ");
  Serial.println(a[0]);
  Serial.print("b[0]: ");
  Serial.println(b[0]);
  Serial.print("c1: ");
  Serial.println(c1);
  Serial.print("a[1]: ");
  Serial.println(a[1]);
  Serial.print("b[1]: ");
  Serial.println(b[1]);
  Serial.print("c2: ");
  Serial.println(c2);
  Serial.print("d: ");
  Serial.println(d);
  Serial.print("e: ");
  Serial.println(e);
  Serial.print("f: ");
  Serial.println(f);
  Serial.print("g: ");
  Serial.println(g);
  Serial.print("h: ");
  Serial.println(h);
  Serial.print("H: ");
  Serial.println(H);
  Serial.print("V: ");
  Serial.println(V);


  if ((g > 90) && (h < 90))
  {
    Serial.print("X= ");
    Serial.println(L - cos(180 - g)*V);
    Serial.print("Y= ");
    Serial.println(sin(180 - g)*V);
  }
  else if ((g < 90) && (h < 90))
  {

    Serial.print("X= ");
    Serial.println(L + cos(g)*V);
    Serial.print("Y= ");
    Serial.println(sin(g)*V);
  }
  else if ((g < 90) && (h > 90))
  {

    Serial.print("X= ");
    Serial.println(L + cos(g)*V);
    Serial.print("Y= ");
    Serial.println(sin(g)*V);
  }
  else if ((g == 90))
  {

    Serial.print("X= ");
    Serial.println(L);
    Serial.print("Y= ");
    Serial.println(V);
  }
  else if ((h == 90))
  {
    Serial.print("X= ");
    Serial.println(L + K);
    Serial.print("Y= ");
    Serial.println(H);
  }
  requestBeaconNumber = 0;
  leftCamera.ToSend(REQUESTEDBEACON, requestBeaconNumber);
  rightCamera.ToSend(REQUESTEDBEACON, requestBeaconNumber);
  leftCamera.sendData(9);
  rightCamera.sendData(9);
  delay(200);
}
