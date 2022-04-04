#include "Application.h"

void Application::init(HWND hwnd, Size windowSize)
{
  // Prepare physical display for work.
  // This takes approximately 0.3 seconds.
  display.init(hwnd, windowSize);

  // set the output source (display buffer) to drawing system
  graphics.init(display.getBuffer());

  // init game core
  core.init(controller, graphics);
}

Buffer Application::getBuffer() const
{
  return display.getBuffer();
}

void Application::update()
{
  controller.update();
  core.update();
  display.update();
}
