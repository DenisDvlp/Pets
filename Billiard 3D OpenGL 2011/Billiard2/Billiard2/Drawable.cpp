#include "Drawable.h"
#include "Drawing.h"

void Drawable::visible(bool isVisible)
{
  this->isVisible = isVisible;
}

bool Drawable::visible() const
{
  return isVisible;
}

void Drawable::position(float x, float y, float z)
{
  pos.set(x, y, z);
}

void Drawable::position(const Position& pos)
{
  this->pos = pos;
}

Position& Drawable::position()
{
  return pos;
}

const Position& Drawable::position() const
{
  return pos;
}

void Drawable::init()
{
  onInit();
}

void Drawable::draw(GLUquadric* quadric) const
{
  if (!isVisible)
    return;

  positionBlock;
  ::position(pos);
  onDraw(quadric);
}
