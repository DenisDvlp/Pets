#include "Application.h"

static Application app;

// Data model LP32 for Arduino Pro Micro
// sizeof(char)      1
// sizeof(int)       2
// sizeof(short)     2
// sizeof(long)      4
// sizeof(long long) 8
// sizeof(void*)     2

void setup() {
  app.init();
}

void loop() {
  app.update();
}
