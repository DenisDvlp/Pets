#pragma once
#undef PI
#undef min
#undef max

template<typename T>
inline T min(T a, T b) { return a < b ? a : b; }

template<typename T>
inline T max(T a, T b) { return a > b ? a : b; }

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

template<typename T>
void adjust_line(T& x, T& width, T fitWidth) {
  x = ::max<T>(x, 0);
  width = ::max<T>(::min<T>(x + width, fitWidth) - x, 0);
}
