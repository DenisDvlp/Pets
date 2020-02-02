//Utils.h
#pragma once
#include <algorithm>

namespace utils
{
  void sleep(size_t millis);

  template<typename T>
  void normalize(T& first, T& second);

  int random(int min, int max);
  float random(float min, float max, int precision);

  template<typename T>
  T range(T min, const T & value, T max);

  template<typename T1, typename T2>
  bool isInRange(T1 min, const T2 & value, T1 max);

  ///////////////implementation///////////////

  template<typename T>
  void normalize(T& first, T& second)
  {
    if (second < first)
    {
      std::swap(first, second);
    }
  }

  template<typename T>
  T range(T min, const T & value, T max)
  {
    normalize(min, max);
    return value < min ? min : value > max ? max : value;
  }

  template<typename T1, typename T2>
  bool isInRange(T1 min, const T2 & value, T1 max)
  {
    normalize(min, max);
    return min <= value && value <= max;
  }
} // namespace utils