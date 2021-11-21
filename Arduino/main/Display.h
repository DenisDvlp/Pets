#pragma once
#include "stdint.h"
#include "Picture.h"
#include <SPI.h>

class Display {
  // Display dimentions.
  static constexpr int DISPLAY_WIDTH = 128;
  static constexpr int DISPLAY_HEIGHT = 64;
  static constexpr int DISPLAY_NUM_PAGE = 8;
  static constexpr int BITS_IN_BYTE = 8;
  static constexpr int BUF_SIZE = DISPLAY_WIDTH * DISPLAY_HEIGHT / BITS_IN_BYTE;

  uint8_t buffer[BUF_SIZE];
  SPISettings Settings;
public:
  Display();
  void init() const;
  void update() const;
  Buffer getBuffer() const;
private:
  void transfer(const uint8_t* buf, size_t count) const;
  void command(uint8_t cmd) const;
  void command(uint8_t cmd, uint8_t data) const;
  void fillPage(uint8_t pageNum, const uint8_t* buf) const;
};