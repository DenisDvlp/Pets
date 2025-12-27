#ifndef ARDUINO
#include "Arduino.hpp"
#include <chrono>
#include <thread>
#include <algorithm>
#include "framework.h"

void delay(unsigned long ms) {
  std::chrono::milliseconds duration(ms);
  std::this_thread::sleep_for(duration);
}

unsigned long millis() {
  using namespace std::chrono;
  auto t = steady_clock::now().time_since_epoch();
  auto ms = duration_cast<milliseconds>(t).count();
  return static_cast<unsigned long>(ms);
}

void digitalWrite(int, int) {
  // No implementation needed for simulation
}
int digitalRead(int key) {
  return !GetAsyncKeyState(key);
}

long random() {
  return rand();
}

long random(long min, long max) {
  return rand() % (max - min + 1) + min;
}

#endif
