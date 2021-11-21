#pragma once
#include "Picture.h"

class Graphics {
  Buffer buf;
public:
  void init(Buffer buffer);
  void clear();
  void drawPicture(Picture pic, Position pos);
private:
  void drawBits(uint8_t byte, uint8_t bitCount, uint8_t* buf, uint8_t mask, uint8_t bufBitShift);
  void drawLine(const uint8_t* bytes, int preBits, int wholeBytes, int postBits, int preBitsShift, uint8_t* buf, int y);
  void drawLines(const uint8_t* bytes, int bmpWidth, int lineCount, int picPreBits, int wholeBytes, int postBits, int preBitsShift, uint8_t* buf, int y);
  bool adjustSize(int& picI, int& picSize, int& bufI, int& bufSize);
};