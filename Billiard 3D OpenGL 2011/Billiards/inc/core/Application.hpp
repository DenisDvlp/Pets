#pragma once
#include "MainWindow.hpp"
#include "graphics/Director.hpp"
#include "win/ApplicationLoop.hpp"

namespace core {

class Application final {
  public:
    Application(HINSTANCE hInstance);

  private:
    gl::Director m_director{};
    MainWindow m_mainWindow;
    win::ApplicationLoop m_applicationLoop;
};

} // namespace core
