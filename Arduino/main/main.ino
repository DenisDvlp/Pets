/*****************************************************************************
*
* File                : oled.ino
* Hardware Environment: Arduino UNO
* Build Environment   : Arduino
* Version             : V1.0.7
*
*                 (c) Copyright 2005-2017, WaveShare
*                      http://www.waveshare.com
*                      http://www.waveshare.net
*                         All Rights Reserved
*
*****************************************************************************/
#include "sh1106.h"
#include "Picture.h"

uint8_t oled_buf[WIDTH * HEIGHT / 8];

uint8_t b[WIDTH * NUM_PAGE] = { 0 };

void fill() {
  b[0] = 0b10000001;
  for (size_t i = 1; i < WIDTH * NUM_PAGE; i++)
  {
    b[i] = 0b0;
  }
}

void setup() {
  delay(500);
  digitalWrite(LED_BUILTIN_RX, HIGH);
  digitalWrite(LED_BUILTIN_TX, HIGH);
  digitalWrite(4, INPUT_PULLUP);
  digitalWrite(5, INPUT_PULLUP);
  digitalWrite(6, INPUT_PULLUP);
  digitalWrite(7, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.print("OLED Example\n");

  SH1106_begin();

  command(0x02);
  SH1106_display(b);
  delay(2000);

  //command(0xB0 + 0);
  //command(0x02);
  //command(0x10);
  //digitalWrite(OLED_DC, HIGH);

  //SPIWrite(0b10000001);
  //SPIWrite(0b01000010);
  //SPIWrite(0b00100100);
  //SPIWrite(0b00011000);
  //SPIWrite(0b00011000);
  //SPIWrite(0b00100100);
  //SPIWrite(0b01000010);
  //SPIWrite(0b10000001);

  //SPIWrite(0b10101010);

  const Bitmap& bmp = nupogodi11;

  SH1106_picture(bmp.ptr, bmp.width, bmp.height, 0, 0, bmp.width, bmp.height, oled_buf, 0, 0, WIDTH, HEIGHT);
  //SH1106_bitmap(0, 0, bmp.ptr, bmp.width, bmp.height, oled_buf);
  SH1106_display(oled_buf);


}


void loop() {

}
