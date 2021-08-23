#pragma once

using uint8_t = int;

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
    : data(data), Size(w, h) {}
};

struct Picture : Position, Size {
  Bitmap* bmp;
  Picture(Bitmap& bmp)
    : bmp(&bmp), Position(0, 0), Size(bmp) {}
  Picture(Bitmap& bmp, int x, int y, int w, int h)
    : bmp(&bmp), Position(x, y), Size(w, h) {}
};

struct Buffer : Size {
  uint8_t* data;
  Buffer(uint8_t* data, int w, int h)
    : data(data), Size(w, h) {}
};

#include "images.gen"