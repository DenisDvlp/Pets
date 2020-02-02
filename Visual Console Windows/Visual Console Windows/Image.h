//Image.h
#pragma once
#include "BiArray.h"
#include "Color.h"
#include "Size.h"
#include <string>

class Image
{
public:
  bool load(std::string);
  bool save(std::string);
  Color* const* pixels();
  const Color* const* pixels() const;
  Size size() const;
private:
  BiArray<Color> m_pixels;
};

