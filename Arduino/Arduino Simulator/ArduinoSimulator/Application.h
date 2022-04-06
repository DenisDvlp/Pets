#pragma once
#include "Graphics.h"
#include "Display.h"
#include "Controller.h"
#include "Core.h"

class Application {
  Graphics graphics;
  Display display;
  Controller controller;
  Core core;
public:
  void init(HWND hwnd, Size windowSize);
  void update();
  Buffer getBuffer() const;
};