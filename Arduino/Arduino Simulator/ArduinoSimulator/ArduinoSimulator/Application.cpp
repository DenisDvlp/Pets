#include "Application.h"
#include "Picture.h"
#include "Images.h"
#include "FontCirillic.h"

void Application::init()
{
  // Prepare physical display for work.
  // This takes approximately 0.3 seconds.
  display.init();

  // set the output source (display buffer) to drawing system
  graphics.init(display.getBuffer());

  // init buttons
  controller.init({ this, &Application::pressDown });

  // init game core
  core.init();

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
  core.update();
  controller.update();
  display.update();
}

template<typename T, size_t S>
constexpr size_t size(T(&)[S]) { return S; }

void Application::pressDown(uint8_t button)
{
  if (button != Controller::BUTTON_X)
    return;
  static int x = 0, y = 0;
  graphics.clear();
  FontCirillic font;
  font.isBold = false;
  Position pos = { (Display::WIDTH - graphics.calculateTextWidth("Ну Погоди", font)) / 2, 20 };
  switch (button) {
  case Controller::BUTTON_X: graphics.drawText("Ну Погоди", pos, font); break;
  //case Controller::BUTTON_Y: graphics.drawPicture(pic_hand, { x,y -= 10 }); break;
  //case Controller::BUTTON_A: graphics.drawPicture(pic_hand, { x,y += 10 }); break;
  //case Controller::BUTTON_B: graphics.drawPicture(pic_hand, { x += 10,y }); break;
  }
}