#pragma once
#include "Picture.hpp"
#include "Font.hpp"

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
  void drawCircle(Position centerPos, int radius);
  void drawPicture(Picture pic, Position pos, bool flip = false, bool transparent = false);
  void drawText(String text, Position pos, const Font& font);
  int calculateTextWidth(String text, const Font& font);
  void fillRect(Position pos, Size size, bool color = true);
private:
  uint8_t* bufferOffset(Position pos);
};
