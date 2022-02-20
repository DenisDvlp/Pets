#pragma once
#ifdef ARDUINO
#include <stdint.h>
#else
#include <cstdint>
#endif

struct Position {
  int x = 0;
  int y = 0;
  constexpr Position() = default;
  constexpr Position(int x, int y)
    : x(x), y(y) {}
};

struct Size {
  int width = 0;
  int height = 0;
  constexpr Size() = default;
  constexpr Size(int w, int h)
    : width(w), height(h) {}
};

struct Bitmap : Size {
  const uint8_t* data = nullptr;
  constexpr Bitmap() = default;
  Bitmap(const uint8_t* data, int w, int h)
    : data(data), Size(w, h) {}
};

struct Picture : Position, Size {
  const Bitmap* bmp = nullptr;
  constexpr Picture() = default;
  Picture(const Bitmap& bmp)
    : bmp(&bmp), Position(0, 0), Size(bmp) {}
  Picture(const Bitmap& bmp, int x, int y, int w, int h)
    : bmp(&bmp), Position(x, y), Size(w, h) {}
};

struct Buffer : Size {
  uint8_t* data = nullptr;
  Buffer() = default;
  Buffer(uint8_t* data, int w, int h)
    : data(data), Size(w, h) {}
};
