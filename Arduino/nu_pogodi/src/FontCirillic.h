#pragma once
#include "Font.h"

class FontCirillic : public Font {
public:
  FontCirillic();
  Picture getPicture(int code) const override;
  int getCharWidth(int code) const override;
  int getSpaceWidth() const override;
  int getCharSpaceWidth() const override;
  int getCharHeight() const override;
private:
  const Bitmap* bmps[5];
  const uint8_t* offsets[5];
  int getOffset(int code) const;
};
