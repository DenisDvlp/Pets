#pragma once
#include "MainWindow.hpp"
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
    void runMessageLoop();
    MainWindow m_window;
    gl::Scene m_scene{};
    gl::objects::Square m_square{};
    gl::objects::Light m_light{};
};

} // namespace win
