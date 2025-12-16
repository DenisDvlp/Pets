#pragma once
#include "Picture.hpp"
#ifdef ARDUINO
#include "Arduino.h"
#else
using byte = unsigned char;
#endif

class Font {
public:
  bool isBold = false;
  byte size = 0;
  virtual ~Font() = default;
  virtual Picture getPicture(int code) const { return {}; }
  virtual int getCharWidth(int code) const { return {}; }
  virtual int getCharHeight() const { return {}; }
  virtual int getSpaceWidth() const { return {}; }
  virtual int getCharSpaceWidth() const { return {}; }
};
