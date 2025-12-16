#pragma once
#include "stdint.h"
#include "Graphics.hpp"
#include "Display.hpp"
#include "Controller.hpp"
#include "Core.hpp"

class Application {
  Graphics graphics;
  const Display display;
  Controller controller;
  Core core;
public:
  void init();
  void update();
private:
  void pressDown(uint8_t button);
};
