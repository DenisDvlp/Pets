#include "Screen.h"

Screen::Screen() :
  console(),
  canvas(console.size())
{}

Screen::Screen(CSize size) :
  Screen(size.width(), size.height())
{}

Screen::Screen(int width, int height) :
  console(width, height),
  canvas(console.size())
{}

void Screen::draw(Drawable &drawable) {
  drawable.draw(canvas);
}

void Screen::update() {
  console.draw(canvas);
}
