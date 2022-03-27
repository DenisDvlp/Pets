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
  static int x = 0, y = 0;
  graphics.clear();
  FontCirillic font;
  font.isBold = false;
  std::string text = "! \"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ЁАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзийклмнопрстуфхцчшщъыьэюяё";

  auto draw = [&](int x) {
    font.size = 0;
    Position pos = { x, 0 };
    graphics.drawText(text, pos, font);
    pos.y += font.getCharHeight();
    font.size = 1;
    graphics.drawText(text, pos, font);
    pos.y += font.getCharHeight();
    font.size = 2;
    graphics.drawText(text, pos, font);
    pos.y += font.getCharHeight();
    font.size = 3;
    graphics.drawText(text, pos, font);
    pos.y += font.getCharHeight();
    font.size = 4;
    graphics.drawText(text, pos, font);
  };

  switch (button) {
  case Controller::BUTTON_X:
    draw(x); break;
  case Controller::BUTTON_Y:
    draw(x+=10); break;
  case Controller::BUTTON_A:
    draw(x-=10); break;
  case Controller::BUTTON_B: graphics.drawPicture(pic_hand, { x += 10,y }); break;
  }
}