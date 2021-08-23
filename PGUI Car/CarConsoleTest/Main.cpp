#include "Application.h"
#include "MainObject.h"

void main() {
  Application::instance().addObject(new MainObject);
  Application::instance().run();
}