#include "FontCirillic.h"
#include "Images.h"


const int* FontCirillic::getMapping(char16_t c) const
{
  return mapping + ((c != u'Ё') ? (c - u'А' + 1) : 0) + isBold * 66;
}

Picture FontCirillic::getPicture(char16_t c) const
{
  const int* const mapping = getMapping(c);
  return Picture(bmp_cirillic, *mapping, 0, mapping[1] - *mapping, bmp_cirillic.height);
}

int FontCirillic::getCharWidth(char16_t c) const
{
  const int* const mapping = getMapping(c);
  return mapping[1] - *mapping;
}
