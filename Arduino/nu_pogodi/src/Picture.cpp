#include "Picture.hpp"

Position operator+(const Position& l, const Position& r) {
  return { l.x + r.x, l.y + r.y };
}
Position operator-(const Position& l, const Position& r) {
  return { l.x - r.x, l.y - r.y };
}
Position operator*(const Position& l, float r) {
  return { static_cast<int>(l.x * r), static_cast<int>(l.y * r) };
}
Position operator*(float l, const Position& r) {
  return r * l;
}
