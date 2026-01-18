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

Position operator+(const Position& l, const Position& r);
Position operator-(const Position& l, const Position& r);
Position operator+(const Position& l, int r);
Position operator+(int l, const Position& r);
Position operator-(const Position& l, int r);
Position operator-(int l, const Position& r);
Position operator*(const Position& l, float r);
Position operator*(float l, const Position& r);

struct Size {
  int width = 0;
  int height = 0;
  constexpr Size() = default;
  constexpr Size(int w, int h)
    : width(w), height(h) {}
  constexpr explicit operator Position() const {
    return { width, height };
  }
};

Size operator+(const Size& l, const Size& r);
Size operator-(const Size& l, const Size& r);
Size operator+(const Size& l, int r);
Size operator+(int l, const Size& r);
Size operator-(const Size& l, int r);
Size operator-(int l, const Size& r);
Size operator*(const Size& l, float r);
Size operator*(float l, const Size& r);

struct Bitmap : Size {
  const uint8_t* data = nullptr;
  const uint8_t colorDepth = 0; // Number of bits that are used to encode a color in range [1,8]
  constexpr Bitmap() = default;
  Bitmap(const uint8_t* data, int w, int h, uint8_t colorDepth)
    : Size(w, h), data(data), colorDepth(colorDepth){}
};

struct Picture : Position, Size {
  const Bitmap* bmp = nullptr;
  constexpr Picture() = default;
  Picture(const Bitmap& bmp)
    : Position(0, 0), Size(bmp), bmp(&bmp) {}
  Picture(const Bitmap& bmp, int x, int y, int w, int h)
    : Position(x, y), Size(w, h), bmp(&bmp) {}
};

struct Buffer : Size {
  uint8_t* data = nullptr;
  Buffer() = default;
  Buffer(uint8_t* data, int w, int h)
    : Size(w, h), data(data){}
};
