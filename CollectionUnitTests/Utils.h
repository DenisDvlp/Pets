#pragma once

#undef max
#undef min
#undef pow

namespace utils
{
  int random(int min, int max);
  float random(float min, float max, int precision);

  template<typename T>
  T max(T value1, T value2);

  template<typename T>
  T min(T value1, T value2);

  template<typename T>
  T range(T min, T value, T max);

  template<typename T>
  bool isInRange(T min, T value, T max);

  template<typename T>
  void swap(T &value1, T &value2);

  ///////////////implementation///////////////

  template<typename T>
  T max(T value1, T value2)
  {
    return value1 > value2 ? value1 : value2;
  }

  template<typename T>
  T min(T value1, T value2)
  {
    return value1 < value2 ? value1 : value2;
  }

  template<typename T>
  T range(T min, T value, T max)
  {
    if (max < min)
    {
      swap(max, min);
    }
    return value < min ? min : value > max ? max : value;
  }

  template<typename T>
  inline bool isInRange(T min, T value, T max)
  {
    return min <= value && value <= max;
  }

  template<typename T>
  void swap(T &value1, T &value2)
  {
    T tmp = value1;
    value1 = value2;
    value2 = tmp;
  }
} // namespace utils