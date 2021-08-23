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
  //fill();
  command(0x02);

  SH1106_display(b);
  delay(2000);
  command(0xB0 + 0);
  command(0x02);
  command(0x10);
  digitalWrite(OLED_DC, HIGH);

  SPIWrite(0b10101010);
  SPIWrite(0b01010101);
  SPIWrite(0b10101010);
  SPIWrite(0b01010101);
  SPIWrite(0b10101010);
  SPIWrite(0b01010101);
  SPIWrite(0b10101010);
  SPIWrite(0b01010101);

  command(0xB0 + 1);
  digitalWrite(OLED_DC, HIGH);

  SPIWrite(0b10000000);
  SPIWrite(0b01000000);
  SPIWrite(0b00100000);
  SPIWrite(0b00010000);
  SPIWrite(0b00001000);
  SPIWrite(0b00000100);
  SPIWrite(0b00000010);
  SPIWrite(0b00000001);

  command(0xB0 + 2);
  digitalWrite(OLED_DC, HIGH);

  SPIWrite(0b10000000);
  SPIWrite(0b01000000);
  SPIWrite(0b00100000);
  SPIWrite(0b00010000);
  SPIWrite(0b00001000);
  SPIWrite(0b00000100);
  SPIWrite(0b00000010);
  SPIWrite(0b00000001);

  command(0xB0 + 3);
  digitalWrite(OLED_DC, HIGH);

  SPIWrite(0b10000000);
  SPIWrite(0b01000000);
  SPIWrite(0b00100000);
  SPIWrite(0b00010000);
  SPIWrite(0b00001000);
  SPIWrite(0b00000100);
  SPIWrite(0b00000010);
  SPIWrite(0b00000001);


  command(0xB0 + 4);
  digitalWrite(OLED_DC, HIGH);

  SPIWrite(0b10000000);
  SPIWrite(0b01000000);
  SPIWrite(0b00100000);
  SPIWrite(0b00010000);
  SPIWrite(0b00001000);
  SPIWrite(0b00000100);
  SPIWrite(0b00000010);
  SPIWrite(0b00000001);

  command(0xB0 + 5);
  digitalWrite(OLED_DC, HIGH);


  SPIWrite(0b10000000);
  SPIWrite(0b01000000);
  SPIWrite(0b00100000);
  SPIWrite(0b00010000);
  SPIWrite(0b00001000);
  SPIWrite(0b00000100);
  SPIWrite(0b00000010);
  SPIWrite(0b00000001);

  command(0xB0 + 6);
  digitalWrite(OLED_DC, HIGH);

  SPIWrite(0b10000000);
  SPIWrite(0b01000000);
  SPIWrite(0b00100000);
  SPIWrite(0b00010000);
  SPIWrite(0b00001000);
  SPIWrite(0b00000100);
  SPIWrite(0b00000010);
  SPIWrite(0b00000001);

  command(0xB0 + 7);
  digitalWrite(OLED_DC, HIGH);

  SPIWrite(0b10000000);
  SPIWrite(0b01000000);
  SPIWrite(0b00100000);
  SPIWrite(0b00010000);
  SPIWrite(0b00001000);
  SPIWrite(0b00000100);
  SPIWrite(0b00000010);
  SPIWrite(0b00000001);

  SPIWrite(0b10000000);
  SPIWrite(0b01000000);
  SPIWrite(0b00100000);
  SPIWrite(0b00010000);
  SPIWrite(0b00001000);
  SPIWrite(0b00000100);
  SPIWrite(0b00000010);
  SPIWrite(0b00000001);

  SPIWrite(0b10000000);
  SPIWrite(0b01000000);
  SPIWrite(0b00100000);
  SPIWrite(0b00010000);
  SPIWrite(0b00001000);
  SPIWrite(0b00000100);
  SPIWrite(0b00000010);
  SPIWrite(0b00000001);

  SPIWrite(0b10000000);
  SPIWrite(0b01000000);
  SPIWrite(0b00100000);
  SPIWrite(0b00010000);
  SPIWrite(0b00001000);
  SPIWrite(0b00000100);
  SPIWrite(0b00000010);
  SPIWrite(0b00000001);

  SPIWrite(0b10000000);
  SPIWrite(0b01000000);
  SPIWrite(0b00100000);
  SPIWrite(0b00010000);
  SPIWrite(0b00001000);
  SPIWrite(0b00000100);
  SPIWrite(0b00000010);
  SPIWrite(0b00000001);

  SPIWrite(0b10000000);
  SPIWrite(0b01000000);
  SPIWrite(0b00100000);
  SPIWrite(0b00010000);
  SPIWrite(0b00001000);
  SPIWrite(0b00000100);
  SPIWrite(0b00000010);
  SPIWrite(0b00000001);

  SPIWrite(0b10000000);
  SPIWrite(0b01000000);
  SPIWrite(0b00100000);
  SPIWrite(0b00010000);
  SPIWrite(0b00001000);
  SPIWrite(0b00000100);
  SPIWrite(0b00000010);
  SPIWrite(0b00000001);

  SPIWrite(0b10000000);
  SPIWrite(0b01000000);
  SPIWrite(0b00100000);
  SPIWrite(0b00010000);
  SPIWrite(0b00001000);
  SPIWrite(0b00000100);
  SPIWrite(0b00000010);
  SPIWrite(0b00000001);

  SPIWrite(0b10000000);
  SPIWrite(0b01000000);
  SPIWrite(0b00100000);
  SPIWrite(0b00010000);
  SPIWrite(0b00001000);
  SPIWrite(0b00000100);
  SPIWrite(0b00000010);
  SPIWrite(0b00000001);

  SPIWrite(0b10101010);
  SPIWrite(0b01010101);
  SPIWrite(0b10101010);
  SPIWrite(0b01010101);
  SPIWrite(0b10101010);
  SPIWrite(0b01010101);
  SPIWrite(0b10101010);
  SPIWrite(0b01010101);

  delay(2000);

  /* display an image of bitmap matrix */
  //SH1106_begin();
  //SH1106_clear(oled_buf);
  //SH1106_bitmap(0, 0, Waveshare12864, 128, 64, oled_buf);
  //SH1106_display(oled_buf);
  //delay(2000);
  //SH1106_clear(oled_buf);

  ///* display images of bitmap matrix */
  //SH1106_bitmap(0, 2, Signal816, 16, 8, oled_buf);
  //SH1106_bitmap(24, 2, Bluetooth88, 8, 8, oled_buf);
  //SH1106_bitmap(40, 2, Msg816, 16, 8, oled_buf);
  //SH1106_bitmap(64, 2, GPRS88, 8, 8, oled_buf);
  //SH1106_bitmap(90, 2, Alarm88, 8, 8, oled_buf);
  //SH1106_bitmap(112, 2, Bat816, 16, 8, oled_buf);

  //SH1106_string(0, 52, "MUSIC", 12, 0, oled_buf);
  //SH1106_string(52, 52, "MENU", 12, 0, oled_buf);
  //SH1106_string(98, 52, "PHONE", 12, 0, oled_buf);

  //SH1106_char3216(0, 16, '1', oled_buf);
  //SH1106_char3216(16, 16, '2', oled_buf);
  //SH1106_char3216(32, 16, ':', oled_buf);
  //SH1106_char3216(48, 16, '3', oled_buf);
  //SH1106_char3216(64, 16, '4', oled_buf);
  //SH1106_char3216(80, 16, ':', oled_buf);
  //SH1106_char3216(96, 16, '5', oled_buf);
  //SH1106_char3216(112, 16, '6', oled_buf);

  //SH1106_display(oled_buf);

}


void loop() {

}

