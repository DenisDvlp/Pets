#pragma once
#include "Types.hpp"
#include "Window.hpp"
#include "graphics/Director.hpp"

namespace win {

class MainWindow : public Window {
  public:
    MainWindow(HINSTANCE hInstance, gl::Director& director);

  protected:
    void onCreate() override;
    void onKeyDown(const std::uint8_t keyCode) override;
    void onMouseMove(const std::int32_t x, const std::int32_t y) override;
    void onResize(const std::uint16_t width, const std::uint16_t height) override;
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
