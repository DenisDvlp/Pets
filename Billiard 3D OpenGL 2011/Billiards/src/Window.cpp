#include "Window.hpp"

Window::Window(std::wstring name, HINSTANCE hInstance)
    : name{std::move(name)}, hInstance{hInstance} {
    WNDCLASS wc{};
    wc.lpfnWndProc = Window::WindowProcedure;
    wc.hInstance = hInstance;
    wc.lpszClassName = name.c_str();
    RegisterClass(&wc);
}

bool Window::open(const std::wstring &caption) {
    hwnd = CreateWindowEx(0,                   // Optional window styles.
                          name.c_str(),        // Window class
                          caption.c_str(),     // Window text
                          WS_OVERLAPPEDWINDOW, // Window style

                          // Size and position
                          CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT,

                          NULL,      // Parent window
                          NULL,      // Menu
                          hInstance, // Instance handle
                          this       // Additional application data
    );

    if (hwnd) {
        ShowWindow(hwnd, SW_SHOW);
        return true;
    }
    return false;
}

Window::~Window() { DestroyWindow(hwnd); }

bool Window::OnMessage(UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return true;
    default:
        return false;
    }
}

LRESULT CALLBACK Window::WindowProcedure(HWND hwnd, UINT message, WPARAM wParam,
                                         LPARAM lParam) {
    return DefWindowProc(hwnd, message, wParam, lParam);
    if (message == WM_NCCREATE) {
        auto createStruct = reinterpret_cast<CREATESTRUCT *>(lParam);
        auto self = reinterpret_cast<Window *>(createStruct->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)self);
    } else {
        auto self =
            reinterpret_cast<Window *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        if(self->OnMessage(message, wParam, lParam)){
            return 0;
        }
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
