//Root.h
#pragma once
#include "BasicTypes.h"
#include "Linkable.h"
#include "Figure.h"
#include "Drawable.h"
#include "Primitive.h"

class Root : Linkable, public Drawable
{
public:
  Root();
private:
  void onBoxEnter(Sender);
  void onBoxLeave(Sender);
  void onBoxClick(Sender, Key);
  void onBoxClickUp(Sender, Key);
  void onMouseMove(Point16);
  void onDraw(IDraw*) override;
private:
  Figure m_figure[5];
  Drawable* m_f = nullptr;
  Point16 m_p;
  Primitive m_primitives[12];
};

