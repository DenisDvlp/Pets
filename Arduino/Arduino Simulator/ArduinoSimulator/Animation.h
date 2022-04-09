#pragma once
#include "Function.h"

void delay(unsigned long ms);
unsigned long millis();

class Animation
{
protected:
  unsigned long ms = 0;
  bool active = false;
  int times = -1;
  unsigned long duration = 1000;
public:
  Function<void()> onFinish;
  Animation(unsigned long duration, int times = -1) :
    duration(duration), times(times) {}
  void start()
  {
    if (!active)
    {
      active = true;
      ms = millis();
    }
  }
  void stop()
  {
    active = false;
  }
  float current()
  {
    if (!active)
    {
      return 0.0f;
    }

    const unsigned long period = millis() - ms;
    if (times >= 0 && period >= duration * times)
    {
      active = false;
      onFinish();
      return 1.0f;
    }

    return static_cast<float>(period % duration) / duration;
  }
  virtual void update() {
    void(current());
  }
};

class AnimationSequence
{
  Animation** array;
  int current = 0;
  int size = 0;
public:
  AnimationSequence(Animation** array, int size) :
    array(array), size(size) {}
  void start()
  {
    array[current]->onFinish.assign(this, &AnimationSequence::onFinish);
    array[current]->start();
  }
  void onFinish()
  {
    if (++current < size)
    {
      start();
    }
  }
  void update()
  {
    if (current < size)
    {
      array[current]->update();
    }
  }
};

class FrameAnimation : public Animation
{
public:
  unsigned long frames = 10;
  FrameAnimation(unsigned long frames, unsigned long duration, int times = -1) :
    Animation(duration, times), frames(frames) {}
  unsigned long currentFrame()
  {
    auto result = static_cast<unsigned long>(current() * frames);
    return result < frames ? result : frames - 1;
  }
};

template<typename T>
class ValueAnimation : public Animation {
protected:
  T& value;
  T from, to;
public:
  ValueAnimation(T& value, T from, T to, unsigned long duration, int times = -1) :
    Animation(duration, times), value(value), from(from), to(to) {}
  void update() override
  {
    value = current() * (to - from) + from;
  }
};

