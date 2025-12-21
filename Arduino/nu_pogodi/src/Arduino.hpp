#pragma once
#ifdef ARDUINO
#include <Arduino.h>
#else

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define LED_BUILTIN 13
#define LED_BUILTIN_RX 17
#define LED_BUILTIN_TX 30

using byte = unsigned char;

void delay(unsigned long ms);
unsigned long millis();
void digitalWrite(int, int);
int digitalRead(int);

struct Serial_ {
  void begin(unsigned long) const {}
  void println(const char*) const {}
};

const Serial_ Serial{};

#endif
