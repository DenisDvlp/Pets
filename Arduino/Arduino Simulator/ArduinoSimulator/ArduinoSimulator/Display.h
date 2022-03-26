#pragma once
#include "stdint.h"
#include "Picture.h"

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
public:
  void init() const;
  void update() const;
  Buffer getBuffer() const;
};