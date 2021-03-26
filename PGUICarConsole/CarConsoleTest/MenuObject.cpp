#include "MenuObject.h"

MenuObject::MenuObject() :
  mainRect_(
    Application::instance().width  * 0.4,
    Application::instance().height * 0.2,
    Application::instance().width  * 0.2,
    6
  )
{
  items_[0].set(
    mainRect_.getWidth()  * 0.3 + mainRect_.x,
    mainRect_.getHeight() * 0.3 + mainRect_.y,
    mainRect_.getWidth()  * 0.4,
    1
  );
  items_[1].set(
    mainRect_.getWidth()  * 0.3 + mainRect_.x,
    mainRect_.getHeight() * 0.6 + mainRect_.y,
    mainRect_.getWidth()  * 0.4,
    1
  );
}

void MenuObject::onKeyDown(int key)
{
  switch (key)
  {
  case KEY_ARROW_UP:   choosenIndex_--;                                   break;
  case KEY_ARROW_DOWN: choosenIndex_++;                                   break;
  case KEY_ENTER: message_ = choosenIndex_ ? MESSAGE_EXIT : MESSAGE_PLAY; break;
  default:                                                                break;
  }
  choosenIndex_ = range(0, choosenIndex_, 1);
}

void MenuObject::onDraw(Canvas & canvas)
{
  canvas.drawRect(mainRect_, '/', COLOR_DARKPURPLE, COLOR_DARKRED);
  canvas.clear(COLOR_RED, items_[choosenIndex_]);
  canvas.drawText(items_[0].x, items_[0].y, "PLAY", COLOR_YELLOW, COLOR_TRANSPARENT);
  canvas.drawText(items_[1].x, items_[1].y, "EXIT", COLOR_YELLOW, COLOR_TRANSPARENT);
}

MenuObject::Message MenuObject::getMessage()
{
  return message_;
}

void MenuObject::clearMessage()
{
  message_ = MESSAGE_NONE;
}
