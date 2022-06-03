#include "Utils.h"

template<size_t N>
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

inline float trigFunc(float angle, float(*trig)(float))
{
  static constexpr size_t N = 36000;
  static const TrigLookup<N> lookup(trig);
  static constexpr float Koef = N / 360.0f;
  return lookup.table[static_cast<int>(Koef * angle)];
}

float Cos(float angle)
{
  return trigFunc(angle, cos);
}

float Sin(float angle)
{
  return trigFunc(angle, sin);
}