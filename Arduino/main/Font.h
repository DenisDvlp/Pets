#pragma once
#include "Picture.h"

class Font {
  bool bold = false;
public:
  virtual ~Font() {};
  bool isBold() const
  {
    return bold;
  }
  void setBold(bool isBold)
  {
    bold = isBold;
  }
  virtual Picture getPicture(char c) const = 0;
};
