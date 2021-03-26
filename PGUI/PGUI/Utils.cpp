#include "Utils.h"
#include <cstdlib>

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

int random(int min, int max)
{
  if (max < min)
  {
    swap(max, min);
  }
  return (rand() % 2 << 30 | rand() << 15 | rand()) % (max - min + 1) + min;
}

float random(float min, float max, int precision)
{
  if(max < min)
  {
    swap(max, min);
  }
  float denominator = 1;
  for (int i = 0; i < precision && i < 7; i++)
  {
    denominator *= 10;
  }
  min = int(min * denominator) / denominator;
  max = int(max * denominator) / denominator;
  int total = (int(max * denominator) - int(min * denominator) + 1);
  float rnd = random(0, 0x7FFFFFFF) / float(0x7FFFFFFF);
  float result = int(rnd * total) / denominator + min;
  return result > max ? max : result;
}

template<typename T>
void swap(T &value1, T &value2)
{
  T tmp = value1;
  value1 = value2;
  value2 = tmp;
}