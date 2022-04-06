#pragma once
#include "stdint.h"
#include "Picture.h"
#include <Windows.h>

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
  HWND hwnd;
  Size windowSize;
public:
  void init(HWND hwnd, Size windowSize);
  void update() const;
  Buffer getBuffer() const;
};