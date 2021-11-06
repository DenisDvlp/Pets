#pragma once
#include "stdint.h"

struct Display {
  void init();
  void refresh();
  int getWidth();
  int getHeight();
  uint8_t* getBuffer();
};