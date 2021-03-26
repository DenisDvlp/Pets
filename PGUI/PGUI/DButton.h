#pragma once
#include "Drawable.h"

#define classname DButton
class DButton : public Drawable
{
  property(string, text, value, value);
  property(COLOR, color, value, value);
  property(COLOR, background, value, value);
public:
  virtual void draw(Canvas &canvas);
};

