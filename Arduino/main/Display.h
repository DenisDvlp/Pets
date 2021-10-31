#pragma once
#include <SPI.h>
#include "Picture.h"

// Display dimentions.
static constexpr size_t DISPLAY_WIDTH = 128;
static constexpr size_t DISPLAY_HEIGHT = 64;
static constexpr size_t DISPLAY_NUM_PAGE = 8;

static constexpr size_t BITS_IN_BYTE = 8;

class Display {
private:
  uint8_t buffer[DISPLAY_WIDTH * DISPLAY_HEIGHT / BITS_IN_BYTE];
  SPISettings Settings;
public:
  Display();
  void init();
  void update() const;
  Buffer getBuffer();
private:
  void fillPage(uint8_t pageNum, const uint8_t* buffer) const;
  void command(uint8_t cmd) const;
  void command(uint8_t cmd, uint8_t data) const;
};