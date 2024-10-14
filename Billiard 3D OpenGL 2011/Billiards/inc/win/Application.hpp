#include "Window.hpp"
#include "Windows.hpp"

class Application final {
  public:
    Application(HINSTANCE hInstance);
    void run();
    ~Application();

  protected:
    void runMessageLoop();
    Window m_window;
};
