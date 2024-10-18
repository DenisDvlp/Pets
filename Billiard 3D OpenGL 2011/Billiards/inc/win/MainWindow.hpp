#pragma once
#include "Window.hpp"
#include <string>

namespace win {

class MainWindow : public Window {
  public:
    using Window::Window;

  protected:
    void onCreate() override;
    void onMouseMove(const int x, const int y) override;
    void onResize(const unsigned short width, const unsigned short height) override;
    bool onClose() override;

  protected:
    void createOpenGlRenderingContext();
    void destroyOpenGlRenderingContext();
    HGLRC m_handleOpenGlRenderingContext{};
};

} // namespace win
