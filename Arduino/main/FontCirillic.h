#pragma once
#include "Font.h"

class FontCirillic : public Font {
public:
  virtual Picture getPicture(char c) const;
};
