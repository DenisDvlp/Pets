#pragma once
#include "stdint.h"

using Callback = void(*)(uint8_t id);

class Button {
  bool pressed = false;
  uint8_t id = -1;
  Callback onPressDownCallback = nullptr;
  Callback onPressUpCallback = nullptr;
public:
  void init(uint8_t id, Callback pressDownCallback = nullptr, Callback pressUpCallback = nullptr);
  void update();
};