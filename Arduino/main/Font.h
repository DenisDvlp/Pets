#pragma once
#include "Picture.h"

class Font {
public:
  bool isBold = false;
  int space = 0;
  int letterSpace = 0;
  virtual ~Font() {};
  virtual Picture getPicture(char c) const { return {}; };
  virtual Picture getPicture(char16_t c) const { return {}; };
  virtual int getCharWidth(char c) const { return {}; };
  virtual int getCharWidth(char16_t c) const { return {}; };
};
