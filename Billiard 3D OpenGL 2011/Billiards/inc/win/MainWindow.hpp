#pragma once
#include "Types.hpp"
#include "Window.hpp"
#include "graphics/Director.hpp"
#include <string>

namespace win {

class MainWindow : public Window {
  public:
    MainWindow(HINSTANCE hInstance, gl::Director& director);

  protected:
    void onCreate() override;
    void onMouseMove(const int x, const int y) override;
    void onResize(const unsigned short width, const unsigned short height) override;
    bool onClose() override;

  protected:
    void createOpenGlRenderingContext();
    void destroyOpenGlRenderingContext();
    HGLRC m_handleOpenGlRenderingContext{};
    gl::Director& m_director;
    Point m_windowCenter{};
    Point m_windowCenterOnScreen{};
};

} // namespace win
