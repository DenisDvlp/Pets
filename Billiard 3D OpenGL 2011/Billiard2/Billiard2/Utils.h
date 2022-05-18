#pragma once
#include <xtr1common>
#include <assert.h>

template<typename T>
static constexpr T pi_v = static_cast<T>(3.14159265358979323846);
static constexpr float pi = pi_v<float>;


template<typename T>
inline constexpr T degToRad(T degree) noexcept
{
  return degree * pi_v<T> / 180;
}
template<typename T>
inline constexpr T radToDeg(T radian) noexcept
{
  return radian * 180 / pi_v<T>;
}

template<typename T>
constexpr void adjustInRange(T min, T& what, T max) noexcept
{
  if (what < min)
    what = min;
  else if (what > max)
    what = max;
}

template<typename T>
constexpr void adjustInLoop(T min, T& what, T max) noexcept
{
  assert(min < max);
  if constexpr (std::is_integral_v<T>)
  {
    if (what < min)
      what = max - (min - what) % (max - min);
    else if (what > max)
      what = what % (max - min) + min;
  }
  else
  {
    if (what < min)
      while (what < min) what += 360;
    else if (what > max)
      while (what > max) what -= max;
  }
}