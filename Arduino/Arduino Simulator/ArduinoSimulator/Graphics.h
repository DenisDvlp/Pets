#pragma once
#include "Picture.h"
#include "Font.h"

#ifdef ARDUINO
#include "WString.h"
#else
#include <string>
using String = std::string;
#endif

class Graphics {
  Buffer buf;
public:
  void init(Buffer buffer);
  void clear();
  void drawPixel(Position pos);
  void drawHLine(Position startPos, int size);
  void drawVLine(Position startPos, int size);
  void drawLine(Position startPos, Position endPos);
  void drawCircle(Position centerPos, int raduis);
  void drawPicture(Picture pic, Position pos, bool transparent = false);
  void drawText(String text, Position pos, const Font& font);
  int calculateTextWidth(String text, const Font& font);
private:
  uint8_t* bufferOffset(Position pos);
};
