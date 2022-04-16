#include "Application.h"

static Application app;

// Data model LP32 for Arduino Pro Micro
// sizeof(char)      1
// sizeof(int)       2
// sizeof(short)     2
// sizeof(long)      4
// sizeof(long long) 8
// sizeof(void*)     2

// Minimal size of the project:
// Program size : 3 462 bytes(used 12 % of a 28 672 byte maximum) (0, 57 secs)
// Minimum Memory Usage : 149 bytes(6 % of a 2560 byte maximum)

void setup() {
  app.init();
}

void loop() {
  app.update();
}
