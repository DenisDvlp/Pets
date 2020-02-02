//MouseInteractable.h
#pragma once
#include "Linkable.h"
#include "Signal.h"
#include "Linkable.h"
#include "BasicTypes.h"

class MouseInteractable : Linkable
{
public:
  MouseInteractable();
  Signal<Key> onMouseUp;
  Signal<Key> onMouseDown;
  Signal<Point16> onMouseMove;
  Signal<> onMouseEnter;
  Signal<> onMouseLeave;
  Signal<> onClick;
public:
  Rect16 rect;
private:
  void linkOnMouseUp(Key);
  void linkOnMouseDown(Key);
  void linkOnMouseMove(Point16);
private:
  Point16 m_mousePosition;
  char m_clicked = 0;
  bool m_isEntered = false;
};

