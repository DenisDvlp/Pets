#pragma once
#undef PI

template<typename T>
void swap(T& a, T& b)
{
  T tmp = a;
  a = b;
  b = tmp;
}

template<typename T>
static constexpr T PI = static_cast<T>(3.14159265358979323846);

template<typename T>
inline T degToRad(T degree)
{
  return degree * PI<T> / 180;
}

template<typename T>
inline T radToDeg(T radian)
{
  return radian * 180 / PI<T>;
}
