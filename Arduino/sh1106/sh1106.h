/**
  ******************************************************************************
  * @file    sh1106.h
  * @author  Petrov Denys
  * @version 1.0
  * @date    21-June-2021
  * @brief   This file includes the OLED driver for SH1106 display moudle
  ******************************************************************************
  * @attention
  * Difference between SSD1306 and SH1106:
  * - The SH1106 controller has an internal RAM of 132x64 pixel.
  *   The SSD1306 controller only has 128x64 pixel.
  * - The SSD1306 has an expanded command set over the SH1106.
  *   The SSD1306 also has capability for automatic scrolling. The SH1106 hasn't.
  * - The SH1106 only supports page addressing mode.
  *  The SSD1306 supports special horizontal and vertical addressing modes.  *
  ******************************************************************************
  */
  
#ifndef _SH1106_H_
#define _SH1106_H_

#include <avr/pgmspace.h>

#define VCCSTATE SH1106_SWITCHCAPVCC
#define WIDTH   128
#define HEIGHT   64
#define NUM_PAGE  8

#define OLED_RST 14 
#define OLED_DC  18
#define OLED_CS  10
#define SPI_MOSI 11     /* connect to the DIN pin of OLED */
#define SPI_SCK  13     /* connect to the CLK pin of OLED */

void SH1106_begin();
void SH1106_display(uint8_t* buffer);
void SH1106_clear(uint8_t* buffer);
void SH1106_pixel(int x,int y,char color, uint8_t* buffer);
void SH1106_bitmap(uint8_t x,uint8_t y,const uint8_t *pBmp, uint8_t chWidth, uint8_t chHeight, uint8_t* buffer);
void SH1106_char1616(uint8_t x,uint8_t y,uint8_t chChar, uint8_t* buffer);
void SH1106_char3216(uint8_t x, uint8_t y, uint8_t chChar, uint8_t* buffer);
void SH1106_string(uint8_t x, uint8_t y, const char *pString, uint8_t Size, uint8_t Mode, uint8_t* buffer);
void SPIWrite(uint8_t data);
void SPIWrite(uint8_t data1, uint8_t data2);
void SPIWrite(uint8_t data1, uint8_t data2, uint8_t data3);
void SPIWrite(uint8_t *buffer, size_t bufferLength);
void command(uint8_t cmd);
void command(uint8_t cmd, uint8_t data);
void command(uint8_t cmd, uint8_t data1, uint8_t data2);

extern const uint8_t Font1612[11][32];
extern const uint8_t Font3216[11][64];
extern const uint8_t Signal816[16];
extern const uint8_t Msg816[16];
extern const uint8_t Bat816[16];
extern const uint8_t Bluetooth88[8];
extern const uint8_t GPRS88[8];
extern const uint8_t Alarm88[8];
extern const uint8_t Waveshare12864[1024];


#endif
