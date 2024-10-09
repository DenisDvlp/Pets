#include "Window.hpp"
#include "Windows.hpp"

class Application final {
  public:
    Application(HINSTANCE hInstance);
    void run();
    ~Application();

  private:
    Window m_window;
};
