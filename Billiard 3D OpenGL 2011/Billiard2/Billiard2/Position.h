#pragma once
template<typename T>
struct PositionT {
  T x = 0;
  T y = 0;
  T z = 0;
  constexpr PositionT() = default;
  constexpr PositionT(T x, T y)
    : x(x), y(y) {}
  constexpr PositionT(T x, T y, T z)
    : x(x), y(y), z(z) {}
  PositionT operator-() const
  {
    return { -x, -y, -z};
  }
};

using Position = PositionT<float>;
