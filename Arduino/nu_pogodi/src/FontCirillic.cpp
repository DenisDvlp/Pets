#include "FontCirillic.hpp"
#include "Images.hpp"
#include "ExtIntArray.hpp"

//!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~������������������������������������������������������������������

FontCirillic::FontCirillic() :
  bmps{
    &bmp_font1,
    &bmp_font2,
    &bmp_font3,
    &bmp_font4,
    &bmp_font5,
  },
  offsets{
    font_offsets_font1,
    font_offsets_font2,
    font_offsets_font3,
    font_offsets_font4,
    font_offsets_font5,
  }
{
  isBold = false;
  size = 0; // range [0, 4]
}

inline int FontCirillic::getCharHeight() const
{
  return bmps[size]->height;
}

int FontCirillic::getOffset(int code) const
{
  struct range{ const int from; const int to; };
  // 33-126,1025,1040-1103,1105
  static const range mapping[] = {
    {33, 126},
    {1025, 1025},
    {1040, 1103},
    {1105, 1105},
  };

  int offset = 0;
  for (auto r : mapping) {
    if (code < r.from) return -1;
    if (code <= r.to) return offset + code - r.from;
    offset += r.to - r.from + 1;
  }
  return -1;
}

Picture FontCirillic::getPicture(int code) const
{
  const int offset = getOffset(code);
  const ExtIntArray<int> exBytes(offsets[size], 10);
  const int x1 = exBytes[offset];
  const int x2 = exBytes[offset + 1];
  return Picture(*bmps[size], x1, 0, x2 - x1, getCharHeight());
}

int FontCirillic::getCharWidth(int code) const
{
  const int offset = getOffset(code);
  const ExtIntArray<int> exBytes(offsets[size], 10);
  return exBytes[offset + 1] - exBytes[offset];
}

int FontCirillic::getSpaceWidth() const
{
  return (size + 1) * 2;
}

int FontCirillic::getCharSpaceWidth() const
{
  return 1 + isBold;
}
