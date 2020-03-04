// SystemEvents.h
#pragma once
#include "Signal.h"
#include "DPoint.h"
#include "DSize.h"
#include "Key.h"

class SystemEvents
{
public:
  Signal<Key> onMouseUp;
  Signal<Key> onMouseDown;
  Signal<DPoint> onMouseMove;
  Signal<Key> onMouseDoubleClick;
  Signal<Key> onKeyUp;
  Signal<Key> onKeyDown;
  Signal<DSize> onDisplayResize;
  bool isCapsLockActive();
  bool isNumLockActive();
  bool isScrollLockActive();
  bool isCtrlPressed();
  bool isShiftPressed();
  bool isAltPressed();
private:
  friend class SystemLoop;
  friend class DApplication;
  byte m_keyStates;
};