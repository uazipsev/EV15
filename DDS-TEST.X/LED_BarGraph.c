
#include "LED_BarGraph.h"
#include "mcc_generated_files/i2c1.h"

#ifndef _BV
  #define _BV(bit) (1<<(bit))
#endif

void LEDBsetBrightness(int b, char i2c_addr) {
  if (b > 15) b = 15;
  I2C1_MasterWrite( (HT16K33_CMD_BRIGHTNESS | b),1,i2c_addr,I2C1_MESSAGE_PENDING);
}

void LEDblinkRate(int b, char i2c_addr) {
  if (b > 3) b = 0; // turn off if not sure
  I2C1_MasterWrite( (HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1)),1,i2c_addr,I2C1_MESSAGE_PENDING);
}

void LEDbegin(char i2c_addr) {
  I2C1_MasterWrite(0x21,1,i2c_addr,I2C1_MESSAGE_PENDING);
  LEDblinkRate(HT16K33_BLINK_OFF,i2c_addr);
  LEDBsetBrightness(15,i2c_addr); // max brightness
}

void LEDwriteDisplay(char i2c_addr) {
  I2C1_MasterWrite( (uint8_t)0x00,1,i2c_addr,I2C1_MESSAGE_PENDING);
  I2C1_MasterWrite( &displaybuffer,8,i2c_addr,I2C1_MESSAGE_PENDING);
  /*
  for (uint8_t i=0; i<8; i++) {
    Wire.write(displaybuffer[i] & 0xFF);
    Wire.write(displaybuffer[i] >> 8);
  }
  Wire.endTransmission();
   */
}

void LEDclear(void) {
  for (uint8_t i=0; i<8; i++) {
    displaybuffer[i] = 0;
  }
}

void LEDsetBar(int bar, int color) {
  uint16_t a, c;

  if (bar < 12)
    c = bar / 4;
  else
    c = (bar - 12) / 4;

  a = bar % 4;
  if (bar >= 12)
    a += 4;

  //Serial.print("Ano = "); Serial.print(a); Serial.print(" Cath = "); Serial.println(c);
  if (color == LED_RED) {
    // Turn on red LED.
    displaybuffer[c] |= _BV(a);
    // Turn off green LED.
    displaybuffer[c] &= ~_BV(a+8);
  } else if (color == LED_YELLOW) {
    // Turn on red and green LED.
    displaybuffer[c] |= _BV(a) | _BV(a+8);
  } else if (color == LED_OFF) {
    // Turn off red and green LED.
    displaybuffer[c] &= ~_BV(a) & ~_BV(a+8);
  } else if (color == LED_GREEN) {
    // Turn on green LED.
    displaybuffer[c] |= _BV(a+8);
    // Turn off red LED.
    displaybuffer[c] &= ~_BV(a);
  }
}

