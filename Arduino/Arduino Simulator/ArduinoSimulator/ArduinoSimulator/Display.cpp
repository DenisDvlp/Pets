#include "Display.h"

void Display::init() const
{

}

void Display::update() const
{

}

Buffer Display::getBuffer() const
{
  return { const_cast<uint8_t*>(buffer), WIDTH, HEIGHT };
}