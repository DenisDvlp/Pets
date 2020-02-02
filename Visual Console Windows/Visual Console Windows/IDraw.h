//IDraw.h
#pragma once
#include "BasicTypes.h"
#include "Image.h"
#include "Align.h"
#include "DString.h"

class IDraw
{
public:
  virtual ~IDraw() = default;
  virtual void clear(Color) = 0;
  virtual void drawRect(Rect16, Color) = 0;
  virtual void drawImage(Point16, const Image&) = 0;
  virtual void drawText(Rect16, const DString&, Color, Align) = 0;
  virtual Rect16 calcTextRect(const DString&) = 0;
};