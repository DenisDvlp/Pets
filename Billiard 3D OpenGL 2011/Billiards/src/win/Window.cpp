#include "win/Window.hpp"

namespace win {

Window::Window(HINSTANCE hInstance, std::wstring className, std::wstring caption)
    : m_handleInstance{hInstance}, m_className{std::move(className)}, m_caption{std::move(caption)} {
    registerWindowClass();
}

bool Window::create() {
    if (!m_handleWindow) {
        m_handleWindow = CreateWindowEx(0,                   // Optional window styles.
                                        m_className.c_str(), // Window class
                                        m_caption.c_str(),   // Window text
                                        // WS_DLGFRAME | WS_MAXIMIZE,
                                        WS_OVERLAPPEDWINDOW | WS_VISIBLE, // Window style

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
    if (m_handleWindow) {
        PostMessage(m_handleWindow, WM_CLOSE, 0, 0);
    }
}

void Window::swapBuffers() {
    SwapBuffers(m_handleDeviceContext);
}

Window::~Window() {
    close();
}

void Window::onCreate() {}

void Window::onKeyDown(const std::uint8_t keyCode) {}

void Window::onKeyUp(const std::uint8_t keyCode) {}

void Window::onMouseMove(const std::int32_t x, const std::int32_t y) {}

void Window::onResize(const std::uint16_t width, const std::uint16_t height) {}

bool Window::onClose() {
    return true;
}

bool Window::onMessage(UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_KEYDOWN: {
        onKeyDown(static_cast<std::uint8_t>(wParam));
        return true;
    }
    case WM_KEYUP: {
        onKeyUp(static_cast<std::uint8_t>(wParam));
        return true;
    }
    case WM_MOUSEMOVE: {
        const std::int32_t x = GET_X_LPARAM(lParam);
        const std::int32_t y = GET_Y_LPARAM(lParam);
        onMouseMove(x, y);
        return true;
    }
    case WM_SIZE: {
        const auto width = static_cast<std::uint16_t>(LOWORD(lParam));
        const auto height = static_cast<std::uint16_t>(HIWORD(lParam));
        onResize(width, height);
        // wParam: SIZE_MAXHIDE, SIZE_MAXIMIZED, SIZE_MAXSHOW, SIZE_MINIMIZED, SIZE_RESTORED
        return true;
    }
    case WM_CLOSE: {
        if (onClose()) {
            destroy();
            PostQuitMessage(0); // stop the main loop of the application
        }
        return true;
    }
    default: {
        return false;
    }
    }
}

Window* Window::getSelfPtr(HWND hwnd) {
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
        self->m_handleWindow = hwnd;
        self->m_handleDeviceContext = GetDC(hwnd);
        self->onCreate();
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

void Window::destroy() {
    if (m_handleWindow) {
        // Setting this to 0 prevents getting `this` from `getSelfPtr` that in turn disables `windowProcedure`
        SetWindowLongPtr(m_handleWindow, GWLP_USERDATA, 0);
        ReleaseDC(m_handleWindow, m_handleDeviceContext);
        m_handleDeviceContext = 0;
        DestroyWindow(m_handleWindow);
        m_handleWindow = 0;
    }
}

void Window::registerWindowClass() {
    WNDCLASS wc{};
    wc.lpfnWndProc = Window::windowProcedure;
    wc.hInstance = m_handleInstance;
    wc.lpszClassName = m_className.c_str();
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);
}

} // namespace win
