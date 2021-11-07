#pragma once
#include "stdint.h"
#include "Graphics.h"
#include "Display.h"
#include "Controller.h"

class Application {
  Graphics graphics;
  Display display;
  Controller controller;
public:
  void init();
  void update();
private:
  void pressDown(uint8_t button);
};