#include "FontCirillic.h"
#include "Images.h"

Picture FontCirillic::getPicture(char c) const
{
  static const uint8_t mapping[] = { 7,9,7,6,10,8,8,13,6,8,8,8,8,10,8,9,8,9,6,8,8,11,8,10,8,12,14,10,10,8,7,13,7 };
  static const uint8_t pageHeight = 17 + isBold() * 34;
  c += 32;
  int x = 0;
  for (uint8_t i = 0; i < sizeof(mapping); i++)
  {
    x += mapping[i];
  }
  return Picture(bmp_cirillic, 0, 0, mapping[c] , pageHeight);
}
