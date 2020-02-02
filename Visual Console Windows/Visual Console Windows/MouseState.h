//MouseState.h
#pragma once
#include <xstring>

class MouseState
{
  using byte = unsigned char;
public:
  static const byte NONE    = 0;
  static const byte LEFT    = 0b0'0001;
  static const byte RIGHT   = 0b0'0010;
  static const byte MIDDLE1 = 0b0'0100;
  static const byte MIDDLE2 = 0b0'1000;
  static const byte MIDDLE  = MIDDLE1 | MIDDLE2;

  static std::string toString(byte);
};