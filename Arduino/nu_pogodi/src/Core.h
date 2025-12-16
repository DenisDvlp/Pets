#pragma once
#include "stdint.h"
#include "Controller.h"
#include "Graphics.h"

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