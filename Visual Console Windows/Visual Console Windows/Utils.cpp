//Utils.cpp
#include <cstdlib>
#include <thread>
#include <chrono>
#include "Utils.h"

namespace utils
{
  void sleep(size_t millis)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
  }

  int random(int min, int max)
  {
    normalize(min, max);
    return (rand() % 2 << 30 | rand() << 15 | rand()) % (max - min + 1) + min;
  }

  float random(float min, float max, int precision)
  {
    normalize(min, max);
    float denominator = float(pow(10, range(0, precision, 7)));
    min = int(min * denominator) / denominator;
    max = int(max * denominator) / denominator;
    int total = (int(max * denominator) - int(min * denominator) + 1);
    float rnd = random(0, 0x7FFFFFFF) / float(0x7FFFFFFF);
    float result = int(rnd * total) / denominator + min;
    return std::min(result, max);
  }
} // namespace utils