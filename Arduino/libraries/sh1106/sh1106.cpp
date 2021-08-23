/**
  ******************************************************************************
  * @file    sh1106.cpp
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

#include <SPI.h>

#include "sh1106.h"

void command(uint8_t cmd){
    digitalWrite(OLED_DC, LOW);
    SPIWrite(cmd);
}

void command(uint8_t cmd, uint8_t data){
    digitalWrite(OLED_DC, LOW);
    SPIWrite(cmd, data);
}

void command(uint8_t cmd, uint8_t data1, uint8_t data2){
    digitalWrite(OLED_DC, LOW);
    SPIWrite(cmd, data1, data2);
}

// первый параметр влияет на скорость передачи данных на дисплей
// это заметно по тому как заполняются страницы
static SPISettings Settings(/*Speed up to 16M Hz*/8000000, MSBFIRST, SPI_MODE0);

void SPIWrite(uint8_t data) {
  SPI.beginTransaction(Settings);
  SPI.transfer(data);
  SPI.endTransaction();
}

void SPIWrite(uint8_t data1, uint8_t data2) {
  SPI.beginTransaction(Settings);
  SPI.transfer(data1);
  SPI.transfer(data2);
  SPI.endTransaction();
}

void SPIWrite(uint8_t data1, uint8_t data2, uint8_t data3) {
  SPI.beginTransaction(Settings);
  SPI.transfer(data1);
  SPI.transfer(data2);
  SPI.transfer(data3);
  SPI.endTransaction();
}

void SPIWrite(uint8_t *buffer, size_t count) {
  SPI.beginTransaction(Settings);
  SPI.transfer(buffer, count);
  SPI.endTransaction();
}

void SH1106_begin()
{
    pinMode(OLED_RST, OUTPUT);
    pinMode(OLED_DC, OUTPUT);
    pinMode(OLED_CS, OUTPUT);
    SPI.begin();

    // http://microsin.net/adminstuff/hardware/ssd1306-oled-controller.html

    // GDDRAM - Graphic Display Data RAM
    // COM - Common Drivers 
    // SEG - Segment Drivers
    
    // D/C - Data/Command
    // DC говорит какая информация будет передаваться:
    // 0 - команда (non-graphics data)
    // 1 - данные, которые будут переданы в GDDRAM (The GDDRAM column address pointer will be increased by one automatically after each data write.)

    // CS(aka SS) говорит какому устройству информация будет передаваться:
    // 0 - устройство принимает данные
    // 1 - устройство игнорирует данные
    digitalWrite(OLED_CS, LOW);
    digitalWrite(OLED_RST, HIGH);
    delay(10);
    digitalWrite(OLED_RST, LOW);
    delay(10);
    digitalWrite(OLED_RST, HIGH);
    
    // Выключить экран
    command(0xAE);//--turn off oled panel

    // Установка адреса начальной страницы
    // 0xB0 + X[2:0]:
    // 0-7 адрес начальной страницы GDDRAM(PAGE0~PAGE7)
    // Примечание: эта команда используется только для Page Addressing Mode.
    //command(0xB0);

    // Устанавливает младший полубайт регистра начального адреса столбца для режима адресации страниц
    // 0x00 + X[3:0]:
    // 0-F (по умолчанию 0)
    // Примечание: эта команда используется только для Page Addressing Mode.
    //command(0x02);//---set low column address

    // Устанавливает старший полубайт регистра начального адреса столбца для режима адресации страниц.
    // 0x10 + X[3:0]:
    // 0-F (по умолчанию 0)
    // Примечание: эта команда используется только для Page Addressing Mode.
    //command(0x10);//---set high column address

    // X[5:0]: 0-63 - регистр начальной строки
    command(0x40);//--set start line address  Set Mapping GDDRAM Display Start Line (0x00~0x3F)

    // установка контраста экрана.
    // X[7:0]:
    // 0-255 - контраст, где 0 это наименьший. (127 по умолчанию)
    command(0x81, 100);//--set contrast control register

    // Отражение изображения по горизонтали.
    // 0xA0 + X[0]:
    // 1 - счёт колонок слева направо 
    // 0 - счёт колонок справа налево
    command(0xA1);//--Set SEG/Column Mapping (0xA1, 0xA0)

    // Отражение изображения по вертикали.
    // 0xC8 - счёт рядов сверху вниз, сканирование от COM[N-1] до COM0, где N - MUX ratio.
    // 0xC0 - счёт рядов снизу вверх, сканирование от COM0 до COM[N-1]. (по умолчанию)
    command(0xC8);//Set COM/Row Scan Direction  (0xC8, 0xC0)

    // в режиме инверсии активные пиксели не будут светиться, а неактивные будут.
    // 0xA6 + X[0]:
    // 0 - нормальный (по умолчанию)
    // 1 - инвертированный
    command(0xA7);//--set display normal(0xA6)/inverse(0xA7)

    // количество рядов используемое на экране снизу вверх. всё что выше не будет отрисовано
    // 0x00-0x3F - количество рабочих рядов.
    // Установка коэффициента мультиплексирования (MUX ratio) для N+1 MUX.
    // X[5:0]:
    // 0-14 - недопустимы
    // 15-63 - 16MUX до 64MUX, где - 63 это 64MUX. (63 по умолчанию)
    command(0xA8, 63);//--set multiplex ratio(1 to 64) and 1/64 duty

    // магия
    command(0xAD, 0x8B); // Set Charge Pump

    command(0x32); /* set VPP 8V (0x30-0x33)*/

    //сдвиг картинки вверх по вертикали
    // X[5:0]:
    // 0-64 - сдвиг начала строк по одной строке вверх (0 по умолчанию)
    command(0xD3, 0);//-set display offset. Shift Mapping GDDRAM Counter (0x00~0x3F) not offset

    // Частота кадров.
    // X[3:0] F:
    // 0-F - коэфициент деления внутреннего генератора, где - 0 минимальная частота
    // X[7:4] D:
    // 0-F - коэффициент деления от 1 до 16, где - 0 это 1
    // Формула. Частота кадров = F / (D · 54 · N), где N устанавливается командой 0xA8
    command(0xD5, 0x80);//--set display clock divide ratio/oscillator frequency. Set divide ratio, Set Clock as 100 Frames/Sec

    // установка периода Phase 1 и Phase 2
    // X[3:0]:
    // 0 - недопустимо
    // 1-15 установка периода Phase 1 (2 по умолчанию)
    // X[7:4]:
    // 0 - недопустимо
    // 1-15 установка периода Phase 2 (2 по умолчанию)
    command(0xD9, 0xF2);//--set Pre-Charge / Discharge period

    // конфигурация выводов COM.
    // 0x02 + X[5:4]:
    // X[4]:
    // 0 - конфигурация последовательных выводов COM.
    // 1 - альтернативная конфигурация выводов COM. (по умолчанию)
    // X[5]:
    // 0 - Disable COM Left / Right remap.(по умолчанию)
    // 1 - Enable COM Left / Right remap.
    command(0xDA, 0x12);//--set com pins hardware configuration

    // Эта команда настраивает выход регулятора напряжения VCOMH.
    // X[6:4]:
    // 0x00 ~0.65 · VCC
    // 0x20 ~0.77 · VCC (по умолчанию)
    // 0x30 ~0.83 · VCC
    command(0xDB, 0x40);//--Set VCOMH Deselect Level

    // Memory Addressing Mode
    // 0 - Horizontal Addressing Mode
    // 1 - Vertical Addressing Mode
    // 2 - Page Addressing Mode (значение по умолчанию после сброса)
    // 3 - недопустимый режим
    // SH1106 поддерживает только Page Addressing Mode
    //command(0x20, 0x00);//-Set Page Addressing Mode

    // Устанавливает младший полубайт регистра начального адреса столбца для режима адресации страниц
    // 0x00 + X[3:0]:
    // 0-F (по умолчанию 0)
    // Примечание: эта команда используется только для Page Addressing Mode.
    // SH1106 имеет 132x64 RAM, и экран центрирован относительно RAM, потому первый пиксель имеет адрес (2,0)
    //command(0x02);//---set low column address

    // Устанавливает старший полубайт регистра начального адреса столбца для режима адресации страниц.
    // 0x10 + X[3:0]:
    // 0-F (по умолчанию 0)
    // Примечание: эта команда используется только для Page Addressing Mode.
    //command(0x10);//---set high column address

    // Настройка адреса начального и конечного столбца.
    // A[6:0]:
    // 0-127 - адрес начального столбца (по умолчанию 0).
    // B[6:0]:
    // 0-127 - адрес конечного столбца (по умолчанию 127).
    // Примечание: эта команда используется только для режимов горизонтальной или вертикальной адресации.
    // Не работает для SH1106
    //command(0x21, 0, 127);//---Set Column Address
    
    // Настройка адреса начальной и конечной страницы.
    // A[2:0]:
    // 0-7 - адрес начального столбца (по умолчанию 0).
    // B[2:0]:
    // 0-7 - адрес конечного столбца (по умолчанию 7).
    // Примечание: эта команда используется только для режимов горизонтальной или вертикальной адресации.
    // Не работает для SH1106
    //command(0x22, 0, 7);//---Set Page Address

    // активировать все пиксели на экране.
    // экран будет весь тупо светиться и перезапись данными не изменит этого состояния.
    // 0xA4 + X[0]:
    // 0 - нет (по умолчанию)
    // 1 - да
    command(0xA4);// Disable Entire Display On

    // Включить экран
    command(0xAF);//--turn on oled panel

    delay(100);
}

void SH1106_clear(uint8_t* buffer)
{
  int i;
  for (i = 0; i < WIDTH * HEIGHT / 8; i++)
  {
    buffer[i] = 0;
  }
}

void SH1106_pixel(int x, int y, bool color, uint8_t* buffer)
{
    if(x >= WIDTH || y >= HEIGHT)return;
    if(color)
        buffer[x+(y/8)*WIDTH] |= 1<<(y%8);
    else
        buffer[x+(y/8)*WIDTH] &= ~(1<<(y%8));
}

// This function relies on the fact that buffer has vertical mapping and LSB-first.
void SH1106_picture(const uint8_t* bmp, int bmpW, int bmpH, int picX, int picY, int picW, int picH, uint8_t* buffer, int bufX, int bufY, int bufW, int bufH)
{
  constexpr uint8_t BITS_IN_BYTE = 2;
  const int startBitInByte = picX % BITS_IN_BYTE;
  const int bytesInPicWidth = (picW / BITS_IN_BYTE) + bool(startBitInByte);
  const int bytesInBmpWidth = bmpW / BITS_IN_BYTE;
  const int startByteInBmpRow = picX / BITS_IN_BYTE;
  int startByteInBmp = startByteInBmpRow + (picY * bytesInBmpWidth);

  // for each row
  for (int i = 0; i < picH; ++i, ++bufY, bufX -= picW, startByteInBmp += bytesInBmpWidth)
  {
    // for each byte in a row
    for (int i = 0, bitX = startBitInByte; i < bytesInPicWidth; ++i, bitX = 0)
    {
      uint8_t byte = pgm_read_byte(bmp + startByteInBmp + i);
      while (bitX < BITS_IN_BYTE)
      {
        const bool color = (byte >> bitX++ & 1); // read byte
        SH1106_pixel(bufX++, bufY, color, buffer); // write bit
      }
    }
  }
}

void SH1106_bitmap(uint8_t x, uint8_t y, const uint8_t *bmp, uint8_t width, uint8_t height, uint8_t* buffer)
{
  static const uint8_t masks[] = {
    0b10000000,
    0b01000000,
    0b00100000,
    0b00010000,
    0b00001000,
    0b00000100,
    0b00000010,
    0b00000001,
  };
  uint8_t byteWidth = (width + 7) / 8;
  for (uint8_t i = 0; i < height; ++i)
  {
    for (uint8_t j = 0; j < byteWidth; ++j)
    {
      uint8_t byte = pgm_read_byte(bmp + j + i / 8);
      for (uint8_t k = 0; k < sizeof(masks); ++k)
      {
        bool pixel = byte & masks[k] >> 7 - k;
        SH1106_pixel(x + j, y + i, pixel, buffer);
      }
    }

  }


    /*uint8_t i, j, byteWidth = (width + 7) / 8;
    for(j = 0; j < height; ++j){
        for(i = 0;i < width; ++i){
            if(pgm_read_byte(bmp +j*byteWidth+i/8) & (128 >> (i & 7))){
                SH1106_pixel(x+i,y+j,1,buffer);
            }
        }
    }*/
}

void SH1106_display(uint8_t* buffer)
{
    uint8_t page;
    uint8_t *pBuf = buffer;
    for (page = 0; page < NUM_PAGE; page++) {
        command(0xB0 + page);
        command(0x02, 0x10);
        digitalWrite(OLED_DC, HIGH);
        SPIWrite(pBuf, WIDTH);
        pBuf += WIDTH;
    }
}
