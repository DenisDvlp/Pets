#pragma once
#include "Canvas.h"
#include "Collection.h"
#include "Macros.h"

#define classname Drawable
class Drawable
{
protected:
  CRect rect;
public:
  virtual void draw(Canvas &canvas) {
    canvas.drawText(rect, "drawable", COLOR_WHITE, COLOR_BLACK, 0, false);
  };
  virtual ~Drawable() {};

  setget(int, x, rect.x(value).x(), rect.x());
  setget(int, y, rect.y(value).y(), rect.y());
  setget(int, width, rect.width(value).width(), rect.width());
  setget(int, height, rect.height(value).height(), rect.height());
};

