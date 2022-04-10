#pragma once
#include "Function.h"

using milliseconds = unsigned long;

void delay(milliseconds ms);
milliseconds millis();

class Animation {
protected:
  bool active = false;
  virtual void onStart(milliseconds now) {}
  virtual void onStop() {}
  virtual void onUpdate(milliseconds now) {}
public:
  Function<void()> onFinish;
public:
  virtual ~Animation() {}
  void start(milliseconds now)
  {
    if (!active)
    {
      active = true;
      onStart(now);
    }
  }
  void stop()
  {
    active = false;
    onStop();
  }
  void restart(milliseconds now)
  {
    stop();
    start(now);
  }
  bool isActive() const
  {
    return active;
  }
  void update(milliseconds now)
  {
    if (active)
    {
      onUpdate(now);
      if (!active)
      {
        onFinish();
      }
    }
  }
};

class DelayAnimation : public Animation {
protected:
  milliseconds ms = 0;
  milliseconds duration = 0;
public:
  DelayAnimation(milliseconds duration) : duration(duration) {}
  void onStart(milliseconds now) override
  {
    ms = now;
  }
  void onUpdate(milliseconds now) override
  {
    if ((now - ms) >= duration)
    {
      stop();
    }
  }
};

class FractionAnimation : public DelayAnimation {
protected:
  const unsigned times = 0;
protected:
  virtual void onFraction(float fraction) {}
public:
  FractionAnimation(milliseconds duration, unsigned times = 0) :
    DelayAnimation(duration), times(times) {}
  void onUpdate(milliseconds now) override
  {
    const milliseconds period = now - ms;
    if (times && period >= duration * times)
    {
      stop();
      onFraction(1.0f);
    }
    else
    {
      onFraction(static_cast<float>(period % duration) / duration);
    }
  }
};

class FrameAnimation : public FractionAnimation {
protected:
  unsigned frames = 10;
  unsigned frame = 0;
public:
  FrameAnimation(unsigned frames, milliseconds duration, int times = -1) :
    FractionAnimation(duration, times), frames(frames) {}
  void onFraction(float part) override
  {
    frame = static_cast<unsigned>(part * frames);
    if (frame >= frames)
    {
      frame = frames - 1;
    }
  }
  unsigned getCurrentFrame() const
  {
    return frame;
  }
};

template<typename T>
class ValueAnimation : public FractionAnimation {
protected:
  T& value;
  T from, to;
public:
  ValueAnimation(T& value, T from, T to, milliseconds duration, int times = -1) :
    FractionAnimation(duration, times), value(value), from(from), to(to) {}
  void onFraction(float part) override
  {
    value = part * (to - from) + from;
  }
};

class SequenceAnimation : public Animation {
protected:
  Animation** animations;
  milliseconds lastNow = 0;
  unsigned size = 0;
  unsigned current = 0;
  unsigned times = 0;
public:
  SequenceAnimation(Animation* animations[], unsigned number, unsigned times = 0) :
    animations(animations), size(number), times(times) {}
  void onStart(milliseconds now) override
  {
    current = 0;
    animations[current]->onFinish.assign(this, &SequenceAnimation::onAnimationFinish);
    animations[current]->start(now);
  }
  void onStop() override
  {
    if (current < size)
    {
      animations[current]->stop();
    }
  }
  void onUpdate(milliseconds now) override
  {
    if (current < size)
    {
      lastNow = now;
      animations[current]->update(now);
    }
  }
  void onAnimationFinish()
  {
    if (++current < size)
    {
      animations[current]->onFinish.assign(this, &SequenceAnimation::onAnimationFinish);
      animations[current]->start(lastNow);
    }
    else {
      if (times == 1)
      {
        stop();
      }
      else
      {
        if (times > 1)
        {
          --times;
        }
        restart(lastNow);
      }
    }
  }
};

