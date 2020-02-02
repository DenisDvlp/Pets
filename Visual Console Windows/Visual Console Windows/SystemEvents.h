// SystemEvents.h
#pragma once
#include "Signal.h"
#include "BasicTypes.h"
#include "IDraw.h"

class SystemEvents
{
public:
  Signal<Key> onMouseUp;
  Signal<Key> onMouseDown;
  Signal<Point16> onMouseMove;
  Signal<Key> onMouseDoubleClick;
  Signal<Key> onKeyUp;
  Signal<Key> onKeyDown;
  Signal<Size16> onDisplayResize;
  Signal<IDraw*> onDraw;
  bool isCapsLockActive();
  bool isNumLockActive();
  bool isScrollLockActive();
  bool isCtrlPressed();
  bool isShiftPressed();
  bool isAltPressed();
private:
  friend class SystemLoop;
  byte m_keyStates;
};