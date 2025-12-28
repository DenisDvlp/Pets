#pragma once
#include "stdint.h"
#include "Controller.hpp"
#include "Graphics.hpp"

class Stage;

class Core {
private:
  Controller* controller;
  Graphics* graphics;
  Stage* stage;
public:
  void init(Controller &c, Graphics &g);
  void update();
private:
  void pressDown(uint8_t button);
};
