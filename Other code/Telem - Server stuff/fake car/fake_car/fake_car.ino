#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"
#include <stdlib.h>

// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ 3  // MUST be an interrupt pin!
#define ADAFRUIT_CC3000_VBAT 5 // Apparently these can be any two pins
#define ADAFRUIT_CC3000_CS 10  // But I wouldn't change these...
// Use hardware SPI for the remaining pins (On a Mega 2560, SCK = 52, MISO = 50, and MOSI = 51)
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIVIDER);

#define WLAN_SSID       "Johnson's"        // cannot be longer than 32 characters!
#define WLAN_PASS       "dd58fa07"
#define WLAN_SECURITY WLAN_SEC_WPA2


String readString = String(100); //string for fetching data from address
uint32_t ip = 3232235901; // This translates into the ip address we need
                          // 3232235901; 192.168.0.125
                          
int randNumber1;
int randNumber2;
int randNumber3;
byte buf[4]; 

void setup(){
  Serial.begin(115200); //Can also work at 9600
  randomSeed(analogRead(0));
  //Initialise CC3000 module
  Serial.println(F("\nInitializing CC3000..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    while(1);
  }
  //Connect to the Wireless Access Point
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }

  Serial.println(F("Connected!"));

  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP()) { //Obtain IP addeess
    delay(100);
  } 

  while (! displayConnectionDetails())
  {
    delay(1000);
  }
 
}

void loop(){
  Adafruit_CC3000_Client client = cc3000.connectTCP(ip, 51238);
  while(1){
  if (client.connected()) {
     randNumber1 = random(0,60);
     randNumber2 = random(300);
     randNumber3 = random(1000);
     client.print('$');
     client.print(highByte(randNumber1));
     client.print(',');
     client.print(lowByte(randNumber1));
     client.print(',');
     client.print(highByte(randNumber2));
     client.print(',');
     client.print(lowByte(randNumber2));
     client.print(',');
     client.print(highByte(randNumber3));
     client.print(',');
     client.print(lowByte(randNumber3));
     client.print('/r');
     Serial.println("Done");
  }
  //Once we have obtained the data, disconnect from the server
  //client.close();
  delay(1000);
  }
}

bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;

  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    Serial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    Serial.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
    Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    Serial.println();
    return true;
  }
}
