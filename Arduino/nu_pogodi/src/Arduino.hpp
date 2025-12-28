#pragma once

using milliseconds = unsigned long;

#ifdef ARDUINO
#include <Arduino.h>
#else

constexpr auto HIGH = 1;
constexpr auto LOW = 0;

constexpr auto OUTPUT = 1;
constexpr auto INPUT_PULLUP = 2;

constexpr auto LED_BUILTIN = 13;
constexpr auto LED_BUILTIN_RX = 17;
constexpr auto LED_BUILTIN_TX = 30;

using byte = unsigned char;


void delay(unsigned long ms);
unsigned long millis();
void digitalWrite(int, int);
int digitalRead(int);
long random();
long random(long min, long max);

struct Serial_ {
  void begin(unsigned long) const {}
  void println(const char*) const {}
  void println(long) const {}
};

const Serial_ Serial{};

#endif
