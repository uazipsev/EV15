// Reed J.
#include <Adafruit_NeoPixel.h>
#include <FastTransfer.h>
#include <Timers.h>

#define PINLft 5
#define PINRht 3
#define PINCntrl 6
#define PINMtr 4
#define PINCr 2


#define RIGHTMAIN_MAX  25
#define LEFTMAIN_MAX   27
#define MOTORBOX_MAX   8
#define CONTROLBOX_MAX 8
#define CORE_MAX       3
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel LeftMain = Adafruit_NeoPixel(LEFTMAIN_MAX, PINLft, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel RightMain = Adafruit_NeoPixel(RIGHTMAIN_MAX, PINRht, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ControlBox = Adafruit_NeoPixel(CONTROLBOX_MAX, PINCntrl, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel MotorBox = Adafruit_NeoPixel(MOTORBOX_MAX, PINMtr, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel Core = Adafruit_NeoPixel(CORE_MAX, PINCr, NEO_GRB + NEO_KHZ800);


#define CONTROL_ADDRESS            5
#define NAVIGATION_ADDRESS         4
#define PIC_ADDRESS                1
#define MOTOR_ADDRESS              6
#define LED_ADDRESS                2
#define POWER_ADDRESS	           3


FastTransfer LED;
int received[4];
#define STATE 1
#define COLOR 2
#define UPDATE_FLAG 3

int state;
boolean initialized;
// 0 is start up
// 1 is autonomous-UA
// 2 is macro-UA
// 3 is normal-UA
// 4 is christmas
// 5 is party
// 6 is override
// 7 is error

#define CHRISTMAS       4
#define PARTY           5
#define COLOR_OVERRIDE  6
#define STROBE          7
#define POLICE          8
#define RAINBOW         9
#define UA             10
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  //begin easy transfer communications.
  Serial.begin(57600);
  LED.begin(Details(received),LED_ADDRESS,false, &Serial);
  pinMode(13, OUTPUT);
  LeftMain.begin();
  LeftMain.show();
  RightMain.begin();
  RightMain.show();
  ControlBox.begin();
  ControlBox.show();
  MotorBox.begin();
  MotorBox.show();
  Core.begin();
  Core.show();
  state = 0;
  initialized = false;
}

uint8_t red;
uint8_t green;
uint8_t blue;

void loop() {
  if (LED.receiveData()) {
    initialized = false;
    state = received[STATE];
    blue = (uint8_t)((received[COLOR] & 0x001F) << 3); //0000 0000 0001 1111 -> 0000 0000 1111 1000
    green = (uint8_t)((received[COLOR] & 0x07E0) >> 3); //0000 0111 1110 0000 -> 0000 0000 1111 1100
    red  = (uint8_t)((received[COLOR] & 0xF800) >> 8); //1111 1000 0000 0000 -> 0000 0000 1111 1000
  }
  if (state == 0)
  {
    gettingComms();
  }
  if (state == 1 && !initialized)
  {
    colorWipe(Core.Color(0, 0, 255));
    initialized = true;
  }
  if (state == 2 && !initialized)
  {
    colorWipe(Core.Color(255, 0, 255));
    initialized = true;
  }
  if (state == 3 && !initialized)
  {
    colorWipe(Core.Color(0, 255, 0));
    initialized = true;
  }
  if (state == 1 || state == 2 || state == 3)
  {
    UALogo();
  }
  if (state == 6 && !initialized)
  {
    colorWipe(Core.Color(red, green, blue));
    initialized = true;
  }
  if (state == 9)
  {
    rainbow();
  }
  if (state == 4)
  {
    christmas();

  }
  if (state == 7 && !initialized)
  {
    colorWipe(Core.Color(0, 0, 0));
    delay(50);
    colorWipe(Core.Color(red, green, blue));
    initialized = false;
  }
  digitalWrite(13, !digitalRead(13));
  delay(50);



}

void allOff()
{
  for (int i = 0; i < 27; i++)
  {
    if (i < RIGHTMAIN_MAX-6)     RightMain.setPixelColor(i, 0);
    if (i < LEFTMAIN_MAX-6)     LeftMain.setPixelColor(i, 0);
    if (i < MOTORBOX_MAX)     MotorBox.setPixelColor(i, 0);
    if (i < CONTROLBOX_MAX)   ControlBox.setPixelColor(i, 0);
    if (i < CORE_MAX)         Core.setPixelColor(i, 0);
  }

  LeftMain.show();
  RightMain.show();
  ControlBox.show();
  MotorBox.show();
  Core.show();
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c)
{
  for (uint16_t i = 0; i < 27; i++)
  {
    if (i < RIGHTMAIN_MAX-6)    RightMain.setPixelColor(i, c);
    if (i < LEFTMAIN_MAX-6)     LeftMain.setPixelColor(i, c);
    if (i < MOTORBOX_MAX)     MotorBox.setPixelColor(i, c);
    if (i < CONTROLBOX_MAX)   ControlBox.setPixelColor(i, c);
    if (i < CORE_MAX)         Core.setPixelColor(i, c);
  }
  RightMain.show();
  LeftMain.show();
  MotorBox.show();
  ControlBox.show();
  Core.show();
}

void gettingComms() {
  static Timers commTimer(500);
  static boolean count = false;
  if (commTimer.timerDone()) {
    if (count) {
      colorWipe(Core.Color(255, 0, 0));
      count = false;
    }
    else {
      colorWipe(Core.Color(0, 0, 255));
      count = true;
    }
  }
}

void christmas() {
  static long previousTime = 0;
  if (millis() - 20 >= previousTime) 
  {
    static int j = 0;
    static int dirrection = 1;
    for (int i = 0; i < 27; i++) 
    {
      if (i % 5 == 0) 
      {
        RightMain.setPixelColor(i, Core.Color(j, j, j));
        LeftMain.setPixelColor(i, Core.Color(j, j, j));
        MotorBox.setPixelColor(i, Core.Color(j, j, j));
        ControlBox.setPixelColor(i, Core.Color(j, j, j));
        Core.setPixelColor(i, Core.Color(j, j, j));
      }
      if (i % 2 == 0) 
      {
        RightMain.setPixelColor(i, Core.Color(255, 0, 0));
        LeftMain.setPixelColor(i, Core.Color(255, 0, 0));
        MotorBox.setPixelColor(i, Core.Color(255, 0, 0));
        ControlBox.setPixelColor(i, Core.Color(255, 0, 0));
        Core.setPixelColor(i, Core.Color(255, 0, 0));
      }
      else 
      {
        RightMain.setPixelColor(i, Core.Color(0, 255, 0));
        LeftMain.setPixelColor(i, Core.Color(0, 255, 0));
        MotorBox.setPixelColor(i, Core.Color(0, 255, 0));
        ControlBox.setPixelColor(i, Core.Color(0, 255, 0));
        Core.setPixelColor(i, Core.Color(0, 255, 0));
      }
      if (j > 254) 
      {
        dirrection = -1;
      }
      if (j < 1) 
      {
        dirrection = 1;
      }

    }
  }
}





void yellowParadeFade() 
{
  static int dirrection = 1;
  static int j;
  for (int i = 21; i <= 27; i++) 
  {
    if (i % 2 == 0) 
    {
      LeftMain.setPixelColor(i, LeftMain.Color(j, j, 0));
    }
    else {
      LeftMain.setPixelColor(i, LeftMain.Color(255 - j, 255 - j, 0));
    }
    LeftMain.show();
    j = j + dirrection;
    if (j > 254)
    {
      dirrection = -1;
    }
    if (j < 1)
    {
      dirrection = 1;
    }


  }


}

void blueParadeFade() 
{
  static int dirrection = 1;
  static int j = 0;
  for (int i = 19; i <= 27; i++) 
  {
    if (i % 2 == 0) 
    {
      RightMain.setPixelColor(i, RightMain.Color(0, 0, j));
    }
    else
    {
      RightMain.setPixelColor(i, RightMain.Color(0, 0, 255 - j));
    }
    RightMain.show();
    j = j + dirrection;
    if (j > 254)
    {
      dirrection = -1;
    }
    if (j < 1)
    {
      dirrection = 1;
    }


  }


}

void UALogo() 
{
  static long previousTime = 0;
  if (millis() - 20 >= previousTime) 
  {
    blueParadeFade();
    yellowParadeFade();
  }
}

/*
void parade(uint32_t c, uint8_t wait, int startPixel, int endPixel) {
  for(int i=0; i< strip0.numPixels(); i++){
    strip0.setPixelColor(i, 0);
  }

  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 2; q++) {
      for (int i=startPixel; i < endPixel+1; i=i+2) {
        strip0.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip0.show();

      delay(wait);

      for (int i=startPixel; i < endPixel+1; i=i+2) {
        strip0.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
*/
void rainbow() 
{
  uint16_t i, j;

  for (j = 0; j < 256; j++) 
  {
    for (i = 0; i < 27; i++) 
    {
      RightMain.setPixelColor(i, Wheel((i + j) & 255));
      LeftMain.setPixelColor(i, Wheel((i + j) & 255));
      MotorBox.setPixelColor(i, Wheel((i + j) & 255));
      ControlBox.setPixelColor(i, Wheel((i + j) & 255));
      Core.setPixelColor(i, Wheel((i + j) & 255));
    }
    RightMain.show();
    LeftMain.show();
    MotorBox.show();
    ControlBox.show();
    Core.show();
    delay(20);
  }
}
/*
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip0.numPixels(); i++) {
      strip0.setPixelColor(i, Wheel(((i * 256 / strip0.numPixels()) + j) & 255));
    }
    strip0.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip0.numPixels(); i=i+3) {
        strip0.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip0.show();

      delay(wait);

      for (int i=0; i < strip0.numPixels(); i=i+3) {
        strip0.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip0.numPixels(); i=i+3) {
          strip0.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip0.show();

        delay(wait);

        for (int i=0; i < strip0.numPixels(); i=i+3) {
          strip0.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}
*/
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return Core.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return Core.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return Core.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

