//MouseState.h
#pragma once
#include <xstring>

class MouseState
{
  using byte = unsigned char;
public:
  static const byte NONE       = 0;
  static const byte LEFT       = 0b0'000001;
  static const byte RIGHT      = 0b0'000010;
  static const byte MIDDLE1    = 0b0'000100;
  static const byte MIDDLE2    = 0b0'001000;
  static const byte MIDDLE     = MIDDLE1 | MIDDLE2;
  static const byte WHEEL_DOWN = 0b0'010000;
  static const byte WHEEL_UP   = 0b0'100000;

  static std::string toString(byte);
};