#pragma once
#include "MainWindow.hpp"
#include "Windows.hpp"
#include "graphics/Director.hpp"

namespace win {

class Application final {
  public:
    Application(HINSTANCE hInstance);
    void run();

  private:
    bool init();
    void runMessageLoop();
    MainWindow m_window;
    gl::Director m_director{};
};

} // namespace win
