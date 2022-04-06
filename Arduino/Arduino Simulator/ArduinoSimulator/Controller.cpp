#include "Controller.h"

void Controller::init(Callback pressDownCallback, Callback pressUpCallback)
{
  buttons[0].init(BUTTON_X, pressDownCallback, pressUpCallback);
  buttons[1].init(BUTTON_Y, pressDownCallback, pressUpCallback);
  buttons[2].init(BUTTON_A, pressDownCallback, pressUpCallback);
  buttons[3].init(BUTTON_B, pressDownCallback, pressUpCallback);
}

void Controller::update()
{
  for (auto& b : buttons)
  {
    b.update();
  }
}
