
//printer.h
#include "RoboLogo.h"
#include "QRNASA.h"
#include "QR_Code.h"
//#include "logo.cpp"
//#include "qr.cpp"

Adafruit_Thermal printer(16, 17); //(38, 4); //38 is the only good pin.... other nneds to be assinged to bs

int thisguy;
void printerPrint()
{
  thisguy+=1;  
   Serial.begin(9600);
  printer.begin();
  printer.feed(2); 
  delay(5000);
  printer.justify('C');
  delay(1000);
  printer.println("********************");
  delay(9100);
//  printer.printBitmap(342, 320, RoboLogo_data1);
  printer.printBitmap(342, 320, RoboLogo_data1);
  delay(5900);
//  delay(6700);  //Danas last number guess 5/11 9_20
  printer.feed(3);
  printer.justify('C');
  delay(1000);
  printer.boldOn();
  printer.setSize('M');
  printer.println("FEAR THE ROOBOT!");
  printer.feed(2);
  printer.boldOff();
  printer.setSize('S');
  delay(5000);
  printer.justify('C');
  delay(1000);
  printer.underlineOn();
  printer.println("DATA");
  delay(1000);
  printer.underlineOff();
  printer.justify('L');
  printer.println("Voltage:      4.78");
  delay(1000);
  // printer.print(fromCommtoControl.volt, DEC);
  delay(1000);
  printer.println("Amp Hours:    1000");
  delay(1000);
  //float amphours = fromCommtoControl.milliamphours /1000.0; 
  //printer.println(amphours, DEC);
  delay(1000);
  printer.println(" ");
  delay(500);
  printer.justify('C');
  delay(200);
  printer.boldOn();
  printer.println("Have a good day!");
  printer.println(" ");
  printer.println("-From C.H.R.I.S.T.E.E.");
  printer.println(" ");
  printer.boldOff();
  delay(150);
  printer.println(" ");
  printer.println("Check out ");
  printer.println("our Facebook with");
  printer.println(" ");
  printer.println("the QR code below!");
  printer.println(" ");
  

  delay(8000);
  printer.printBitmap(292, 200, QR_Code_data);
  delay(8000);
  
  //  printer.println(" ");
  //  printer.print("12345678901234567890");
  //  printer.println(" ");
  printer.feed(5);//for evenness use 5
}

