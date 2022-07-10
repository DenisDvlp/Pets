#include "Utils.h"

template<size_t N, int>
struct TrigLookup
{
  TrigLookup(float(*trig)(float))
  {
    constexpr float koef = 2.0f * pi;
    for (size_t i = 0; i < N; ++i)
    {
      table[i] = trig(koef * i / N);
    }
  }
  float table[N];
};

template<int Version>
inline float trigFunc(float angle, float(*trig)(float))
{
  static constexpr size_t N = 36000;
  static const TrigLookup<N, Version> lookup(trig);
  static constexpr float Koef = N / 360.0f;
  return lookup.table[static_cast<int>(Koef * angle)];
}

float Cos(float angle)
{
  return trigFunc<1>(angle, cos);
}

float Sin(float angle)
{
  return trigFunc<2>(angle, sin);
}