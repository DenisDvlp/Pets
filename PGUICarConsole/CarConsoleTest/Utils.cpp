#include "Utils.h"
#include <cstdlib>

Rect::Rect() {}
Rect::Rect(int x, int y, int width, int height)
{
  set(x, y, width, height);
}
int Rect::getRight()
{
  return x + width_;
}
int Rect::getBottom()
{
  return y + height_;
}
int Rect::getWidth()
{
  return width_;
}
int Rect::getHeight()
{
  return height_;
}
void Rect::setWidth(int width)
{
  width_ = max(0, width);
}
void Rect::setHeight(int height)
{
  height_ = max(0, height);
}
void Rect::set(int x, int y, int width, int height)
{
  this->x = x;
  this->y = y;
  setWidth(width);
  setHeight(height);
}
Rect Rect::intersectRect(Rect rect)
{
  Rect r;
  r.x = max(x, rect.x);
  r.y = max(y, rect.y);
  r.setWidth( min(getRight(),  rect.getRight())  - r.x);
  r.setHeight(min(getBottom(), rect.getBottom()) - r.y);
  return r;
}
bool Rect::hasPoint(int x, int y)
{
  return
    x >= this->x && x < getRight() &&
    y >= this->y && y < getBottom();
}

bool Rect::isIntersectRect(Rect rect)
{
  rect = intersectRect(rect);
  return rect.width_ && rect.height_;
}

bool Rect::isEmpty()
{
  return !(width_ | height_);
}

int max(int value1, int value2)
{
  return value1 > value2 ? value1 : value2;
}

int min(int value1, int value2)
{
  return value1 < value2 ? value1 : value2;
}

int range(int min, int value, int max)
{
  return value < min ? min : value > max ? max : value;
}

float range(float min, float value, float max)
{
  return value < min ? min : value > max ? max : value;
}

int random(int min, int max)
{
  return rand() % (max - min + 1) + min;
}
