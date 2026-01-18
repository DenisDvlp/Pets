#pragma once
#include "Function.hpp"
#include "Arduino.hpp"


// Path is the sequence of values that linearly change over their durations
//
// First and last values are where the animation starts and ends.
// Duration in the first item is a delay before starting the animation
template<typename T>
struct Path {
  T value{};
  milliseconds duration = 0;
  Path() = default;
  Path(const T& value, milliseconds duration) : value(value), duration(duration) {}
};

template<typename T>
class Animation {
  const Path<T> simplePath[2]{};
protected:
  T& value;
  const Path<T>* first = nullptr;
  const Path<T>* last = nullptr;
  const Path<T>* current = nullptr;
  milliseconds startMs = 0;
  int times = -1;
  int currentTimes = 0;
public:
  Function<void()> onFinish;

  // Edge case. Has an embedded Path array of two items.
  Animation(T& value, T from, T to, milliseconds duration, int times = -1, milliseconds delay = 0)
    : simplePath{ {from, delay}, {to, duration} }, value(value), first(simplePath), last(simplePath + 1), times(times) {}
  // General case. Takes Path array of any size.
  template<size_t S>
  Animation(T& value, const Path<T>(&path)[S], int times = -1)
    : value(value), first(path), last(path + S - 1), times(times) {}
  Animation(T& value, const Path<T>* begin, const Path<T>* end, int times = -1)
    : value(value), first(begin), last(end - 1), times(times) {}

  void start(milliseconds now) {
    if (startMs == 0 && times != 0) {
      current = first;
      currentTimes = times;
      startMs = now + first->duration;
      if (first->duration == 0)
        value = first->value;
    }
  }

  void stop() {
    startMs = 0;
    current = nullptr;
    value = last->value;
  }

  void update(milliseconds now) {
    if(startMs == 0 || startMs > now)
      return;

    milliseconds currentDuration = now - startMs;
    while (currentDuration > (current + 1)->duration) {
      currentDuration -= (current + 1)->duration;
      startMs += (current + 1)->duration;
      ++current;
      if (current == last) {
        if (currentTimes < 0 || currentTimes-- > 1) {
          // Start over
          current = first;
          startMs = now;
          value = first->value;
        } else {
          onFinish();
          stop();
        }
        return;
      }
    }
    const auto fraction = static_cast<float>(currentDuration) / (current + 1)->duration;
    value = current->value + ((current + 1)->value - current->value) * fraction;
  }
};
