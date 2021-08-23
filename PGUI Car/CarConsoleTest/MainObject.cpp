#include "MainObject.h"

MainObject::MainObject()
{
  menu_.isEnabled = menu_.isVisible = false;
  game_.isEnabled = game_.isVisible = true;
  Application::instance().addObject(&menu_);
  Application::instance().addObject(&game_);
}

void MainObject::onKeyDown(int key)
{
  switch (key)
  {
  case KEY_ESC:
    if(!menu_.isVisible)
    {
      menu_.isEnabled = menu_.isVisible = true;
      game_.isEnabled = game_.isVisible = false;
      menu_.clearMessage();
    }
    else
    {
      menu_.isEnabled = menu_.isVisible = false;
      game_.isEnabled = game_.isVisible = true;
      menu_.clearMessage();
    }
    break;
  case KEY_ENTER:
    if (game_.isVisible)
    {
      game_.isEnabled = !game_.isEnabled;
    }
    break;
  default: break;
  }
}

void MainObject::onUpdate()
{
  if (menu_.getMessage() == MenuObject::MESSAGE_PLAY)
  {
    menu_.isEnabled = menu_.isVisible = false;
    game_.isEnabled = game_.isVisible = true;
    menu_.clearMessage();
  }
  else if (menu_.getMessage() == MenuObject::MESSAGE_EXIT)
  {
    Application::instance().close();
  }
}
