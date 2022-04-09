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
  void drawBits(uint8_t byte, uint8_t bitCount, uint8_t* buf, uint8_t mask, uint8_t bufBitShift, bool transparent);
  void drawLine(const uint8_t* bytes, int preBits, int wholeBytes, int postBits, int preBitsShift, uint8_t* buf, int y, bool transparent);
  void drawLines(const uint8_t* bytes, int bmpWidth, int lineCount, int picPreBits, int wholeBytes, int postBits, int preBitsShift, uint8_t* buf, int y, bool transparent);
  bool adjustSize(int& picI, int& picSize, int& bufI, int bufSize);
};