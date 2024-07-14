#define WIN32_LEAN_AND_MEAN // Исключите редко используемые компоненты из
                            // заголовков Windows
#include <string>
#include <windows.h>
#include <assert.h>

class Window2 {
  public:
    Window2(const wchar_t *name, HINSTANCE hInstance);
    bool open(const wchar_t *text);
    ~Window2();

    LRESULT OnMessage(UINT message, WPARAM wParam, LPARAM lParam);

  protected:
    std::wstring name;
    HINSTANCE hInstance;
    HWND hwnd;
};

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam,
                                 LPARAM lParam);

Window2::Window2(const wchar_t *name, HINSTANCE hInstance)
    : name{name}, hInstance{hInstance} {
    WNDCLASS wc{};
    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = hInstance;
    wc.lpszClassName = name;
    RegisterClass(&wc);
}

bool Window2::open(const wchar_t *text) {
    hwnd = CreateWindowEx(0,                   // Optional window styles.
                          name.c_str(),        // Window2 class
                          text,                // Window2 text
                          WS_OVERLAPPEDWINDOW, // Window2 style

                          // Size and position
                          CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT,

                          NULL,      // Parent window
                          NULL,      // Menu
                          hInstance, // Instance handle
                          this       // Additional application data
    );

    if (hwnd != NULL) {
        ShowWindow(hwnd, 1);
    }

    return (hwnd != NULL);
}

Window2::~Window2() { DestroyWindow(hwnd); }

LRESULT Window2::OnMessage(UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CLOSE:
        return DefWindowProc(hwnd, message, wParam, lParam);
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam,
                                 LPARAM lParam) {

    if (message == WM_NCCREATE) {
        auto createStruct = reinterpret_cast<CREATESTRUCT *>(lParam);
        auto self = reinterpret_cast<Window2 *>(createStruct->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)self);
        return DefWindowProc(hwnd, message, wParam, lParam);
    } else {
        // auto self =
        //     reinterpret_cast<Window2 *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        // if(!self)
        //     assert("fuck");
        // self->OnMessage(message, wParam, lParam);
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;

    // if (message == WM_NCCREATE) {
    //     auto createStruct = reinterpret_cast<CREATESTRUCT *>(lParam);
    //     auto self = reinterpret_cast<Window2 *>(createStruct->lpCreateParams);
    //     SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)self);
    //     return DefWindowProc(hwnd, message, wParam, lParam);
    // } else {
    //     auto self =
    //         reinterpret_cast<Window2 *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    //     self->OnMessage(message, wParam, lParam);
    // }
    // return DefWindowProc(hwnd, message, wParam, lParam);

    switch (message) {
    case WM_NCCREATE: {
        auto createStruct = reinterpret_cast<CREATESTRUCT *>(lParam);
        auto self = reinterpret_cast<Window2 *>(createStruct->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)self);
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

class Application2 {
  public:
    Application2(HINSTANCE hInstance);
    void run();
    ~Application2();

  private:
    Window2 window;
};

Application2::Application2(HINSTANCE hInstance)
    : window{L"Billiards", hInstance} {}

void Application2::run() {
    window.open(L"MyBilliards");

    while (1) {
        MSG msg;
        while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                return;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}

Application2::~Application2() {}

static LRESULT WindowProc(HWND hwnd, UINT message, WPARAM wp, LPARAM lp) {
    switch (message) {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wp, lp);
    }
    return 0;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hprev, LPSTR cmdline, int show) {

    Application2 app(hInstance);
    app.run();
    return 0;
}
