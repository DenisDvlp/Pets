//Image.h
#pragma once
#include "DColor.hpp"
#include "DSize.hpp"
#include "DBiArray.hpp"
#include <string>

class DImage
{
public:
  bool load(std::string);
  bool save(std::string);
  DColor* data();
  const DColor* data() const;
  DColor* const* pixels();
  const DColor* const* pixels() const;
  DSize size() const;
  DColor* const operator[](size_t);
  const DColor* const operator[](size_t) const;
private:
  DBiArray<DColor> m_pixels;
};
