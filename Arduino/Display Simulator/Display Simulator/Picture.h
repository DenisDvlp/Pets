#pragma once
#include <cassert>

using uint8_t = unsigned char;

struct Position {
  int x = 0;
  int y = 0;
  Position() = default;
  Position(int x, int y)
    : x(x), y(y) {}
};

struct Size {
  int width;
  int height;
  Size() = default;
  Size(int w, int h)
    : width(w), height(h) {}
};

struct Bitmap : Size {
  const uint8_t* data;
  Bitmap(const uint8_t* data, int w, int h)
    : data(data), Size(w, h) {
    assert(data, "Bitmap data shall be nonnull.");
    assert(w > 0 && h > 0, "Dimensions shall be bigger then zero.");
    assert(!(w % 8) , "Width shall be a multiple of 8.");
  }
};

struct Picture : Position, Size {
  const Bitmap* bmp;
  Picture(const Bitmap* bmp)
    : bmp(bmp), Position(0, 0), Size(*bmp) {}
  Picture(const Bitmap* bmp, int x, int y, int w, int h)
    : bmp(bmp), Position(x, y), Size(w, h) {
    assert(bmp, "Bitmap shall be nonnull.");
    assert(x >= 0 && y >= 0 && w >= 0 && h >= 0,
      "Dimensions shall not be negative.");
    assert(x + w <= bmp->width && y + h <= bmp->height,
      "Picture bounds shall be within the bitmap.");
  }
};

struct Buffer : Size {
  uint8_t* data;
  Buffer(uint8_t* data, int w, int h)
    : data(data), Size(w, h) {
    assert(data, "Buffer data shall be nonnull.");
    assert(w > 0 && h > 0, "Dimensions shall be bigger then zero.");
    assert(!(h % 8), "Height shall be a multiple of 8.");
  }
};

#include "images.gen"