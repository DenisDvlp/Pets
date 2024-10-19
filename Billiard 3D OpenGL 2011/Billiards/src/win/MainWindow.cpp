#include "win/MainWindow.hpp"

namespace win {

MainWindow::MainWindow(HINSTANCE hInstance, gl::Director& director)
    : Window(hInstance, L"billiard_main_window", L"Billiards by Denys Petrov 2024"), m_director{director} {}

void MainWindow::onCreate() {
    createOpenGlRenderingContext();
    m_director.init();
}

void MainWindow::onMouseMove(const int x, const int y) {}

void MainWindow::onResize(const unsigned short width, const unsigned short height) {
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
