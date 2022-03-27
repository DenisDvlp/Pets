#include "Application.h"

void Application::init()
{
  // Prepare physical display for work.
  // This takes approximately 0.3 seconds.
  display.init();

  // set the output source (display buffer) to drawing system
  graphics.init(display.getBuffer());

  // init game core
  core.init(controller, graphics);

  // clean display
  graphics.clear();
  display.update();
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
