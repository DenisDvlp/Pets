#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include "Console.h"
#include "Canvas.h"
#include "Object.h"

class Application
{
  static const int delay = 30;
  static const int keyCount = 256;
  bool opened_ = true;
  Console console_;
  Canvas canvas_;
  bool keyStates_[keyCount] = { 0 };
  std::vector<Object*> objects_;

  Application();
  void checkKeyboard();
  void update();
public:
  const int width = 0;
  const int height = 0;
  static Application& instance();
  void close();
  void addObject(Object *object);
  void removeObject(Object *object);
  void run();
};

#endif // APPLICATION_H