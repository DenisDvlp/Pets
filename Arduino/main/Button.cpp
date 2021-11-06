#include "Button.h"
#include "Arduino.h"

void Button::init(uint8_t id, Callback pressDownCallback, Callback pressUpCallback)
{
  this->id = id;
  onPressDownCallback = pressDownCallback;
  onPressUpCallback = pressUpCallback;
  digitalWrite(id, INPUT_PULLUP);
}

void Button::update()
{
  const bool triggered = !digitalRead(id);
  if (pressed ^ triggered) {
    pressed = triggered;
    if (triggered)
    {
      if (onPressDownCallback)
        return onPressDownCallback(id);
    }
    else
    {
      if (onPressUpCallback)
        return onPressUpCallback(id);
    }
  }
}
