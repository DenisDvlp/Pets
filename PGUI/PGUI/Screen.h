#pragma once
#include "Console.h"
#include "Canvas.h"
#include "Drawable.h"

#define classname Screen
class Screen
{
  Console console;
  Canvas canvas;
public:
  Screen();
  Screen(CSize size);
  Screen(int width, int height);

  getter(int, width, console.width());
  getter(int, height, console.height());
  setget(short, fontSize, console.fontSize(value), console.fontSize());

  void draw(Drawable &drawable);
  void update();
};

