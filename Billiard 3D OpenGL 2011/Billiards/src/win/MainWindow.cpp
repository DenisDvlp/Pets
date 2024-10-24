#include "win/MainWindow.hpp"

namespace win {

MainWindow::MainWindow(HINSTANCE hInstance, gl::Director& director)
    : Window(hInstance, L"billiard_main_window", L"Billiards by Denys Petrov 2024"), m_director{director} {}

void MainWindow::onCreate() {
    createOpenGlRenderingContext();
    m_director.init();
}

void MainWindow::onKeyDown(const std::uint8_t keyCode) {
    switch (keyCode) {
    case 0x41: // A
    {
        m_director.camera.move.left = true;
        break;
    }
    case 0x44: // D
    {
        m_director.camera.move.right = true;
        break;
    }
    case 0x57: // W
    {
        m_director.camera.move.forward = true;
        break;
    }
    case 0x53: // S
    {
        m_director.camera.move.backward = true;
        break;
    }
    default: {
        return;
    }
    }
}
void MainWindow::onKeyUp(const std::uint8_t keyCode) {
    switch (keyCode) {
    case 0x41: // A
    {
        m_director.camera.move.left = false;
        break;
    }
    case 0x44: // D
    {
        m_director.camera.move.right = false;
        break;
    }
    case 0x57: // W
    {
        m_director.camera.move.forward = false;
        break;
    }
    case 0x53: // S
    {
        m_director.camera.move.backward = false;
        break;
    }
    default: {
        return;
    }
    }
}

void MainWindow::onMouseMove(const std::int32_t x, const std::int32_t y) {
    static constexpr float mouseSensitivity = 0.2f;
    m_director.camera.rotation.y() += (x - m_windowCenter.x) * mouseSensitivity;
    m_director.camera.rotation.x() += (y - m_windowCenter.y) * mouseSensitivity;
    SetCursorPos(m_windowCenterOnScreen.x, m_windowCenterOnScreen.y);
}

void MainWindow::onResize(const std::uint16_t width, const std::uint16_t height) {
    m_windowCenter.x = width / 2;
    m_windowCenter.y = height / 2;

    POINT point{width / 2, height / 2};
    ClientToScreen(m_handleWindow, &point);
    m_windowCenterOnScreen.x = point.x;
    m_windowCenterOnScreen.y = point.y;

    m_director.resize(width, height);
}

bool MainWindow::onClose() {
    destroyOpenGlRenderingContext();
    return true;
}

void MainWindow::createOpenGlRenderingContext() {
    if (!m_handleOpenGlRenderingContext) {
        // clang-format off
        PIXELFORMATDESCRIPTOR pixelFormatDescriptor{
            sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd
            1,                     // version number
            PFD_DRAW_TO_WINDOW |   // support window
            PFD_SUPPORT_OPENGL |   // support OpenGL
            PFD_DOUBLEBUFFER,      // double buffered
            PFD_TYPE_RGBA,         // RGBA type
            32,                    // 32-bit color depth
            0, 0, 0, 0, 0, 0,      // color bits ignored
            0,                     // no alpha buffer
            0,                     // shift bit ignored
            0,                     // no accumulation buffer
            0, 0, 0, 0,            // accum bits ignored
            32,                    // 32-bit z-buffer
            0,                     // no stencil buffer
            0,                     // no auxiliary buffer
            PFD_MAIN_PLANE,        // main layer
            0,                     // reserved
            0, 0, 0                // layer masks ignored
        };
        // clang-format on
        const int pixelFormat = ChoosePixelFormat(m_handleDeviceContext, &pixelFormatDescriptor);
        SetPixelFormat(m_handleDeviceContext, pixelFormat, &pixelFormatDescriptor);
        m_handleOpenGlRenderingContext = wglCreateContext(m_handleDeviceContext);
        wglMakeCurrent(m_handleDeviceContext, m_handleOpenGlRenderingContext);
    }
}

void MainWindow::destroyOpenGlRenderingContext() {
    if (m_handleOpenGlRenderingContext) {
        wglMakeCurrent(m_handleDeviceContext, NULL);
        wglDeleteContext(m_handleOpenGlRenderingContext);
        m_handleOpenGlRenderingContext = 0;
    }
}

} // namespace win
