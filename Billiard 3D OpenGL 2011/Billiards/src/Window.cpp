#include "Window.hpp"

Window::Window(std::wstring className, std::wstring caption, HINSTANCE hInstance)
    : m_className{std::move(className)}, m_caption{std::move(caption)}, m_hInstance{hInstance} {
    registerWindowClass();
}

void Window::registerWindowClass() {
    WNDCLASS wc{};
    wc.lpfnWndProc = Window::windowProcedure;
    wc.hInstance = m_hInstance;
    wc.lpszClassName = m_className.c_str();
    RegisterClass(&wc);
}

bool Window::create() {
    if (!m_hWnd) {
        m_hWnd = CreateWindowEx(0,                   // Optional window styles.
                                m_className.c_str(), // Window class
                                m_caption.c_str(),   // Window text
                                WS_OVERLAPPEDWINDOW, // Window style

                                // Size and position
                                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

                                NULL,        // Parent window
                                NULL,        // Menu
                                m_hInstance, // Instance handle
                                this         // Additional application data
        );
    }
    return (m_hWnd != 0);
}

void Window::show() {
    if (m_hWnd) {
        ShowWindow(m_hWnd, SW_SHOW);
    }
}

void Window::hide() {
    if (m_hWnd) {
        ShowWindow(m_hWnd, SW_HIDE);
    }
}

void Window::close() {
    DestroyWindow(m_hWnd);
    m_hWnd = 0;
}

Window::~Window() { close(); }

bool Window::onMessage(UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY: {
        m_hWnd = 0;
        PostQuitMessage(0);
        return true;
    }
    default: {
        return false;
    }
    }
}

LRESULT CALLBACK Window::windowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (WM_CREATE != message) {
        if (auto self{reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA))}) {
            if (self->onMessage(message, wParam, lParam)) {
                return 0;
            }
        }
    } else {
        // WM_CREATE
        auto createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
        auto self = reinterpret_cast<Window*>(createStruct->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
