#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Window.hpp"

class Application {
  public:
    Application(HINSTANCE hInstance);
    void run();
    ~Application();

  private:
    Window window;
};
