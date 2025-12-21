#pragma once
#include "stdint.h"
#include "Picture.hpp"

#ifdef ARDUINO
#include <SPI.h>

class Display {
public:
  // Display dimentions.
  static constexpr int WIDTH = 128;
  static constexpr int HEIGHT = 64;
private:
  static constexpr int NUM_PAGE = 8;
  static constexpr int BITS_IN_BYTE = 8;
  static constexpr int BUF_SIZE = WIDTH * HEIGHT / BITS_IN_BYTE;

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
#else

class Display {
private:
  static constexpr int pixelSize = 7;
  static constexpr int pixelInterval = 1;
  static constexpr int offsetHorizontal = 3;
  static constexpr int offsetVertical = 3;
public:
  static constexpr int WIDTH = 128;
  static constexpr int HEIGHT = 64;
  static constexpr int canvasWidth = WIDTH * (pixelSize + pixelInterval) + offsetHorizontal * 2;
  static constexpr int canvasHeight = HEIGHT * (pixelSize + pixelInterval) + offsetVertical * 2;
private:
  static constexpr int NUM_PAGE = 8;
  static constexpr int BITS_IN_BYTE = 8;
  static constexpr int BUF_SIZE = WIDTH * HEIGHT / BITS_IN_BYTE;

  uint8_t buffer[BUF_SIZE];
public:
  void init() const;
  void update() const;
  Buffer getBuffer() const;
};
#endif
