#pragma once
#include "stdint.h"
#include "Function.hpp"

using Callback = Function<void(uint8_t)>;

class Button {
  bool pressed = false;
  uint8_t id = -1;
  Callback onPressDownCallback;
  Callback onPressUpCallback;
public:
  void init(uint8_t id, Callback pressDownCallback = Callback(), Callback pressUpCallback = Callback());
  void update();
};
