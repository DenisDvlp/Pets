#pragma once
#include "Picture.h"
#include "Font.h"
#include <iostream>

class Graphics {
  Buffer buf;
public:
  void init(Buffer buffer);
  void clear();
  void drawPixel(Position pos);
  void drawHLine(Position startPos, int size);
  void drawVLine(Position startPos, int size);
  void drawPicture(Picture pic, Position pos, bool transparent = false);
  void drawText(std::string text, Position pos, const Font& font);
  int calculateTextWidth(std::string text, const Font& font);
private:
  uint8_t* bufferOffset(Position pos);
};
