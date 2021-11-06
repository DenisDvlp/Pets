#include "Application.h"

static Application app;

void setup() {
  app.init();
}

void loop() {
  app.update();
}
