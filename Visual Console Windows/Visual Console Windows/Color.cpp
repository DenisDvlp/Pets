//Color.cpp
#include "Color.h"
#include <sstream>

using byte = unsigned char;

byte Color::Red(int color)
{
  return (color & RED) >> 16;
}

byte Color::Green(int color)
{
  return (color & GREEN) >> 8;
}

byte Color::Blue(int color)
{
  return color & BLUE;
}

Color::Color(int color)
  : r(Red(color))
  , g(Green(color))
  , b(Blue(color))
{}

Color::Color(byte r, byte g, byte b)
  : r(r)
  , g(g)
  , b(b)
{}

void Color::set(byte red, byte green, byte blue)
{
  r = red;
  g = green;
  b = blue;
}

Color & Color::operator=(int color)
{
  r = Red(color);
  g = Green(color);
  b = Blue(color);
  return *this;
}

Color::operator int() const
{
  return value();
}

int Color::value() const
{
  return r << 16 | g << 8 | b;
}

std::string Color::toString()
{
  std::stringstream stream;
  stream << std::hex << value();
  return stream.str();
}
