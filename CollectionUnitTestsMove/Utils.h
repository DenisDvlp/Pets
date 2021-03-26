#pragma once

#undef max
#undef min

namespace utils
{
  int random(int min, int max);
  float random(float min, float max, int precision);

  template<typename T>
  const T & max(const T & value1, const T & value2);

  template<typename T>
  const T & min(const T & value1, const T & value2);

  template<typename T>
  T range(T min, const T & value, T max);

  template<typename T1, typename T2, typename T3>
  bool isInRange(T1 min, const T2 & value, T3 max);

  template<typename T>
  void swap(T &value1, T &value2);

  ///////////////implementation///////////////

  template<typename T>
  const T & max(const T & value1, const T & value2)
  {
    return value1 > value2 ? value1 : value2;
  }

  template<typename T>
  const T & min(const T & value1, const T & value2)
  {
    return value1 < value2 ? value1 : value2;
  }

  template<typename T>
  T range(T min, const T & value, T max)
  {
    if (max < min)
    {
      swap(max, min);
    }
    return value < min ? min : value > max ? max : value;
  }

  template<typename T1, typename T2, typename T3>
  inline bool isInRange(T1 min, const T2 & value, T3 max)
  {
    if (max < min)
    {
      swap(max, min);
    }
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