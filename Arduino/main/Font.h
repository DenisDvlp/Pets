#pragma once
#include "Picture.h"

class Font {
public:
  bool isBold = false;
  byte size = 0;
  virtual ~Font() = default;
  virtual Picture getPicture(char c) const { return {}; };
  virtual Picture getPicture(char16_t c) const { return {}; };
  virtual byte getCharWidth(char c) const { return {}; };
  virtual byte getCharWidth(char16_t c) const { return {}; };
  virtual byte getSpaceWidth() const;
  virtual byte getCharSpaceWidth() const;
};
