#include <cstdlib>
#include "Utils.h"

namespace utils
{
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
    if (max < min)
    {
      swap(max, min);
    }
    float denominator = float(pow(10, range(0, precision, 7)));
    min = int(min * denominator) / denominator;
    max = int(max * denominator) / denominator;
    int total = (int(max * denominator) - int(min * denominator) + 1);
    float rnd = random(0, 0x7FFFFFFF) / float(0x7FFFFFFF);
    float result = int(rnd * total) / denominator + min;
    return utils::min(result, max);
  }
} // namespace utils