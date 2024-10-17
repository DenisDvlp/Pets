#pragma once
#include "MessageLoop.hpp"
#include "Window.hpp"
#include "Windows.hpp"
#include "graphics/Scene.hpp"
#include "objects/Square.hpp"

namespace win {

class Application final {
  public:
    Application(HINSTANCE hInstance);
    void run();

  private:
    bool init();
    Window m_window;
    gl::Scene m_scene{};
    gl::objects::Square m_square{};
    MessageLoop m_messageLoop;
};

} // namespace win
