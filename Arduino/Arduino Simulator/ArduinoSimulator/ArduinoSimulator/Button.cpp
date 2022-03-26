#include "Button.h"

extern bool buttons[];

void Button::init(uint8_t id, Callback pressDownCallback, Callback pressUpCallback)
{
  this->id = id;
  onPressDownCallback = pressDownCallback;
  onPressUpCallback = pressUpCallback;
}

void Button::update()
{
  const bool triggered = buttons[id];
  if (pressed ^ triggered) {
    pressed = triggered;
    if (triggered)
    {
        onPressDownCallback(id);
    }
    else
    {
        onPressUpCallback(id);
    }
  }
}
