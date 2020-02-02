//Color.h
#pragma once
#include <xstring>

class Color
{
  using byte = unsigned char;
public:
  static const int BLACK  = 0x000000;
  static const int RED    = 0xff0000;
  static const int GREEN  = 0x00ff00;
  static const int BLUE   = 0x0000ff;
  static const int CYAN   = GREEN | BLUE;
  static const int YELLOW = RED | GREEN;
  static const int PURPLE = RED | BLUE;
  static const int WHITE  = RED | GREEN | BLUE;
public:
  static byte Red(int color);
  static byte Green(int color);
  static byte Blue(int color);
  std::string toString();
public:
  Color() = default;
  Color(int color);
  Color(byte r, byte g, byte b);
  void set(byte r, byte g, byte b);
  Color& operator=(int color);
  operator int() const;
  int value() const;
  byte r = 0;
  byte g = 0;
  byte b = 0;
};

