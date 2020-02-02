//Clickable.h
#pragma once
#include "Linkable.h"
#include "BasicTypes.h"
#include "Signal.h"

class Clickable : Linkable
{
public:
  Clickable();
  Signal<> onClick;
public:
  Rect16 rect;
private:
  void onMouseUp(Key);
  void onMouseDown(Key);
  void onMouseMove(Point16);
private:
  Point16 m_mousePosition;
  char m_clicked = 0;
};

