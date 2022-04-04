#include "Display.h"
#include <string>

void Display::init(HWND hwnd, Size windowSize)
{
  this->hwnd = hwnd;
  this->windowSize = windowSize;
}

void Display::update() const
{
  // Update the screen only if any pixel has been changed.
  static uint8_t prevBuf[BUF_SIZE] = {};

  bool changed = false;
  for (size_t i = 0; i < BUF_SIZE; ++i)
  {
    if (prevBuf[i] != buffer[i])
    {
      changed = true;
      break;
    }
  }
  if (!changed)
    return;

  memcpy(prevBuf, buffer, BUF_SIZE);

  RECT windowRect = { 0, 0, windowSize.width, windowSize.height };
  InvalidateRect(hwnd, &windowRect, 0);
}

Buffer Display::getBuffer() const
{
  return { const_cast<uint8_t*>(buffer), WIDTH, HEIGHT };
}