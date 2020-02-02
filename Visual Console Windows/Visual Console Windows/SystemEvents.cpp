// SystemEvents.cpp
#include "SystemEvents.h"

bool SystemEvents::isCapsLockActive()
{
  return m_keyStates & KeyState::CAPSLOCK;
}

bool SystemEvents::isNumLockActive()
{
  return m_keyStates & KeyState::NUMLOCK;
}

bool SystemEvents::isScrollLockActive()
{
  return m_keyStates & KeyState::SCROLLLOCK;
}

bool SystemEvents::isCtrlPressed()
{
  return m_keyStates & KeyState::CTRL;
}

bool SystemEvents::isShiftPressed()
{
  return m_keyStates & KeyState::SHIFT;
}

bool SystemEvents::isAltPressed()
{
  return m_keyStates & KeyState::ALT;
}