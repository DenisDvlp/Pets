#include "Window.hpp"
#include "Windows.hpp"
#include "graphics/Scene.hpp"

class Application final {
  public:
    Application(HINSTANCE hInstance);
    void run();
    ~Application();

  protected:
    void runMessageLoop();
    Window m_window;
    gl::Scene m_scene;
};
