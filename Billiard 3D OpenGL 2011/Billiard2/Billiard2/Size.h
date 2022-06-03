#pragma once
template<typename T>
struct SizeT
{
  T width = 0;
  T height = 0;
  constexpr SizeT() = default;
  constexpr SizeT(T width, T height)
    : width(width), height(height) {}
  void set(T width, T height)
  {
    this->width = width;
    this->height = height;
  }
};

using Size = SizeT<size_t>;
