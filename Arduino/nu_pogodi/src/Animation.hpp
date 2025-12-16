#pragma once
#include "Function.hpp"

using milliseconds = unsigned long;

void delay(milliseconds ms);
milliseconds millis();

class Animation {
  friend class SequenceAnimation;
protected:
  bool active = false;
  Function<void()> onAnimationFinish;
protected:
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
        onAnimationFinish();
      }
    }
  }
};

class DelayAnimation : public Animation {
protected:
  milliseconds ms = 0;
  const milliseconds duration = 0;
private:
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
public:
  DelayAnimation(milliseconds duration) : duration(duration) {}
};

class PeriodicAnimation : public DelayAnimation {
protected:
  unsigned times = 0;
private:
  void onUpdate(milliseconds now) override
  {
    if ((now - ms) >= duration)
    {
      onPeriod();
      if (times)
      {
        stop();
      }
      else
      {
        if (times > 1)
        {
          --times;
        }
        restart(now);
      }
    }
  }
public:
  Function<void()> onPeriod;
public:
  PeriodicAnimation(milliseconds period, unsigned times = 0) :
    DelayAnimation(period), times(times) {}
};

class FractionAnimation : public DelayAnimation {
protected:
  const unsigned times = 0;
protected:
  virtual void onFraction(float fraction) {}
private:
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
public:
  FractionAnimation(milliseconds duration, unsigned times = 0) :
    DelayAnimation(duration), times(times) {}
};

class FrameAnimation : public FractionAnimation {
protected:
  unsigned frames = 10;
  unsigned frame = 0;
private:
  void onFraction(float part) override
  {
    frame = static_cast<unsigned>(part * frames);
    if (frame >= frames)
    {
      frame = frames - 1;
    }
  }
public:
  FrameAnimation(unsigned frames, milliseconds duration, int times = -1) :
    FractionAnimation(duration, times), frames(frames) {}
  unsigned getCurrentFrame() const
  {
    return frame;
  }
};

template<typename T>
class ValueAnimation : public FractionAnimation {
protected:
  T& value;
  const T from, to;
private:
  void onFraction(float part) override
  {
    value = part * (to - from) + from;
  }
public:
  ValueAnimation(T& value, T from, T to, milliseconds duration, int times = -1) :
    FractionAnimation(duration, times), value(value), from(from), to(to) {}
};

template<>
class ValueAnimation<bool> : public FractionAnimation {
protected:
  bool& value;
  const bool from, to;
private:
  void onFraction(float part) override
  {
    value = (part == 1.0f) ? to : from;
  }
public:
  ValueAnimation(bool& value, bool from, bool to, milliseconds duration, int times = -1) :
    FractionAnimation(duration, times), value(value), from(from), to(to) {}
};

class SequenceAnimation : public Animation {
protected:
  Animation** animations;
  milliseconds lastNow;
  const unsigned size = 0;
  unsigned current = 0;
  const unsigned times = 0;
  unsigned time = 0;
private:
  void onStart(milliseconds now) override
  {
    current = 0;
    time = times;
    animations[current]->onAnimationFinish.assign(this, &SequenceAnimation::onAnimationFinish);
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
      animations[current]->onAnimationFinish.assign(this, &SequenceAnimation::onAnimationFinish);
      animations[current]->start(lastNow);
    }
    else {
      if (time == 1)
      {
        stop();
      }
      else
      {
        if (time > 1)
        {
          --time;
        }
        restart(lastNow);
      }
    }
  }
public:
  SequenceAnimation(Animation* animations[], unsigned number, unsigned times = 0) :
    animations(animations), size(number), times(times) {}
};
