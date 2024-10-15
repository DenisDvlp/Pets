#include "win/Window.hpp"

Window::Window(std::wstring className, std::wstring caption, HINSTANCE hInstance)
    : m_className{std::move(className)}, m_caption{std::move(caption)}, m_handleInstance{hInstance} {
    registerWindowClass();
}

void Window::registerWindowClass() {
    WNDCLASS wc{};
    wc.lpfnWndProc = Window::windowProcedure;
    wc.hInstance = m_handleInstance;
    wc.lpszClassName = m_className.c_str();
    RegisterClass(&wc);
}

bool Window::create() {
    if (!m_handleWindow) {
        m_handleWindow = CreateWindowEx(0,                   // Optional window styles.
                                        m_className.c_str(), // Window class
                                        m_caption.c_str(),   // Window text
                                        WS_OVERLAPPEDWINDOW, // Window style

                                        // Size and position
                                        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

                                        NULL,             // Parent window
                                        NULL,             // Menu
                                        m_handleInstance, // Instance handle
                                        this              // Additional application data
        );
    }
    return (m_handleWindow != 0);
}

void Window::show() {
    if (m_handleWindow) {
        ShowWindow(m_handleWindow, SW_SHOW);
    }
}

void Window::hide() {
    if (m_handleWindow) {
        ShowWindow(m_handleWindow, SW_HIDE);
    }
}

void Window::close() {
    destroyOpenGlRenderingContext();
    if (m_handleWindow) {
        DestroyWindow(m_handleWindow);
        m_handleWindow = 0;
    }
}

Window::~Window() { close(); }

bool Window::onMessage(UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY: {
        close();
        PostQuitMessage(0); // stop the main loop of the application
        return true;
    }
    case WM_SIZE: {
        // switch (wParam) {
        // case SIZE_MAXHIDE: {
        //     onResize(LOWORD(lParam), HIWORD(lParam));
        // }
        // case SIZE_MAXIMIZED: {
        //     onResize(LOWORD(lParam), HIWORD(lParam));
        // }
        // case SIZE_MAXSHOW: {
        //     onResize(LOWORD(lParam), HIWORD(lParam));
        // }
        // case SIZE_MINIMIZED: {
        //     onResize(LOWORD(lParam), HIWORD(lParam));
        // }
        // case SIZE_RESTORED: {
        //     onResize(LOWORD(lParam), HIWORD(lParam));
        // }
        // }
        return true;
    }
    default: {
        return false;
    }
    }
}

void Window::createOpenGlRenderingContext() {
    if (!m_handleDeviceContext) {
        return;
    }

    m_handleDeviceContext = GetDC(m_handleWindow);
    // clang-format off
    PIXELFORMATDESCRIPTOR pixelFormatDescriptor{
        sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd
        1,                     // version number
        PFD_DRAW_TO_WINDOW |   // support window
        PFD_SUPPORT_OPENGL |   // support OpenGL
        PFD_DOUBLEBUFFER,      // double buffered
        PFD_TYPE_RGBA,         // RGBA type
        24,                    // 24-bit color depth
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

void Window::destroyOpenGlRenderingContext() {
    if (m_handleDeviceContext) {
        wglMakeCurrent(m_handleDeviceContext, NULL);
        wglDeleteContext(m_handleOpenGlRenderingContext);
        ReleaseDC(m_handleWindow, m_handleDeviceContext);
        m_handleOpenGlRenderingContext = 0;
        m_handleDeviceContext = 0;
    }
}

inline Window* Window::getSelfPtr(HWND hwnd) {
    return reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
}

Window* Window::storeSelfPtr(HWND hwnd, LPARAM lParam) {
    auto createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
    auto self = reinterpret_cast<Window*>(createStruct->lpCreateParams);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
    return self;
}

LRESULT CALLBACK Window::windowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (WM_CREATE != message) {
        if (Window * self{getSelfPtr(hwnd)}) {
            if (self->onMessage(message, wParam, lParam)) {
                return 0;
            }
        }
    } else if (Window * self{storeSelfPtr(hwnd, lParam)}) {
        // WM_CREATE
        self->createOpenGlRenderingContext();
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
