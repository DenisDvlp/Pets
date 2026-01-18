#include "Picture.hpp"

Position operator+(const Position& l, const Position& r) {
  return { l.x + r.x, l.y + r.y };
}
Position operator-(const Position& l, const Position& r) {
  return { l.x - r.x, l.y - r.y };
}
Position operator+(const Position& l, int r) {
  return { l.x + r, l.y + r };
}
Position operator+(int l, const Position& r) {
  return r + l;
}
Position operator-(const Position& l, int r) {
  return { l.x - r, l.y - r };
}
Position operator-(int l, const Position& r) {
  return r - l;
}
Position operator*(const Position& l, float r) {
  return { static_cast<int>(l.x * r), static_cast<int>(l.y * r) };
}
Position operator*(float l, const Position& r) {
  return r * l;
}

Size operator+(const Size& l, const Size& r) {
  return { l.width + r.width, l.height + r.height };
}
Size operator-(const Size& l, const Size& r) {
  return { l.width - r.width, l.height - r.height };
}
Size operator+(const Size& l, int r) {
  return { l.width + r, l.height + r };
}
Size operator+(int l, const Size& r) {
  return r + l;
}
Size operator-(const Size& l, int r) {
  return { l.width - r, l.height - r };
}
Size operator-(int l, const Size& r) {
  return r - l;
}
Size operator*(const Size& l, float r) {
  return { static_cast<int>(l.width * r), static_cast<int>(l.height * r) };
}
Size operator*(float l, const Size& r) {
  return r * l;
}
