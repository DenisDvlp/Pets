#include "Application.h"

static Application app;

// Data models LP32
// sizeof(char)      1
// sizeof(int)       2
// sizeof(short)     2
// sizeof(long)      4
// sizeof(long long) 8
// sizeof(void*)

void setup() {
  app.init();
}

void loop() {
  app.update();
}
