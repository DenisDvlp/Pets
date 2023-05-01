#pragma once

#include "Types.h"

class IInputListener
{
public:

  virtual void OnMouseMove(word x, word y) = 0;
  virtual void OnButton(byte key, bool pressed) = 0;
  ~IInputListener() = default;
};

class Input
{
public:

  Input() = default;
  Input(IInputListener * listener);
  static bool getKeyState(byte key);
  void run();

private:

  IInputListener * mListener = nullptr;
};