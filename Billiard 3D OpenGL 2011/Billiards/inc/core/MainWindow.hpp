#pragma once
#include "RenderingLoop.hpp"
#include "common/Types.hpp"
#include "graphics/Director.hpp"
#include "win/Window.hpp"

namespace core {

class MainWindow final : public win::Window {
  public:
    MainWindow(HINSTANCE hInstance, gl::Director& director);
    void createOpenGlRenderingContext();
    void destroyOpenGlRenderingContext();

  private:
    void onCreate() override;
    void onKeyDown(const std::uint8_t keyCode) override;
    void onKeyUp(const std::uint8_t keyCode) override;
    void onMouseMove(const std::int32_t x, const std::int32_t y) override;
    void onResize(const std::uint16_t width, const std::uint16_t height) override;
    bool onClose() override;

  private:
    gl::Director& m_director;
    common::Point m_windowCenter{};
    common::Point m_windowCenterOnScreen{};
    HGLRC m_handleOpenGlRenderingContext{};
    RenderingLoop m_renderingLoop;
};

} // namespace core
