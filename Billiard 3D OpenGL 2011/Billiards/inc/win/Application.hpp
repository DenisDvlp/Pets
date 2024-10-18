#pragma once
#include "MainWindow.hpp"
#include "MessageLoop.hpp"
#include "Windows.hpp"
#include "graphics/Scene.hpp"
#include "objects/Light.hpp"
#include "objects/Square.hpp"

namespace win {

class Application final {
  public:
    Application(HINSTANCE hInstance);
    void run();

  private:
    bool init();
    MainWindow m_window;
    gl::Scene m_scene{};
    gl::objects::Square m_square{};
    gl::objects::Light m_light{};
    MessageLoop m_messageLoop;
};

} // namespace win
