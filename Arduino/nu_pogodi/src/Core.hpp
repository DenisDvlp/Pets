#pragma once
#include "stdint.h"
#include "Controller.hpp"
#include "Graphics.hpp"

class Core {
private:
  Controller* controller;
  Graphics* graphics;
public:
  void init(Controller &c, Graphics &g);
  void update();
private:
  void pressDown(uint8_t button);
};
