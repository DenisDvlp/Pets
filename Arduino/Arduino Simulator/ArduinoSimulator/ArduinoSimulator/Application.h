#pragma once
#include "Graphics.h"
#include "Display.h"
#include "Controller.h"
#include "Core.h"

class Application {
  Graphics graphics;
  const Display display;
  Controller controller;
  Core core;
public:
  void init();
  void update();
  Buffer getBuffer() const;
};