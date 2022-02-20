#pragma once
#include "Font.h"

class FontCirillic : public Font {
public:
  FontCirillic();
  Picture getPicture(char16_t c) const override;
  byte getCharWidth(char16_t c) const override;
  byte getSpaceWidth() const override;
  byte getCharSpaceWidth() const override;
private:
  const Bitmap* bmps[5];
  const uint8_t* offsets[5];
  byte getCharHeight() const;
  int getOffset(char16_t c) const;
};
