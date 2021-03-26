#include "Sizable.h"

Sizable::~Sizable() {}

int Sizable::width()
{
  return m_size.width();
}

void Sizable::width(int width)
{
  m_size.width(width);
  onResize();
}

int Sizable::height()
{
  return m_size.height();
}

void Sizable::height(int height)
{
  m_size.height(height);
  onResize();
}

CSize Sizable::size()
{
  return m_size;
}

void Sizable::size(CSize size)
{
  this->size(size.width(), size.height());
}

void Sizable::size(int width, int height)
{
  m_size.set(width, height);
  onResize();
}