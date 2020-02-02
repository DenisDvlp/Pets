//KeyState.h
#pragma once
#include <xstring>

class KeyState
{
  using byte = unsigned char;
public:
  static const byte NONE = 0;
  static const byte CAPSLOCK   = 0b0'1000'0000;
  static const byte SCROLLLOCK = 0b0'0100'0000;
  static const byte NUMLOCK    = 0b0'0010'0000;
  static const byte SHIFT      = 0b0'0001'0000;
  static const byte CTRL_L     = 0b0'0000'1000;
  static const byte CTRL_R     = 0b0'0000'0100;
  static const byte ALT_L      = 0b0'0000'0010;
  static const byte ALT_R      = 0b0'0000'0001;
  static const byte CTRL       = CTRL_L | CTRL_R;
  static const byte ALT        = ALT_L  | ALT_R;

  static std::string toString(byte);
};
