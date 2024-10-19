#include "win/Application.hpp"

namespace win {

Application::Application(HINSTANCE hInstance) : m_window{hInstance, m_director} {}

void Application::run() {
    if (init()) {
        runMessageLoop();
    }
}

bool Application::init() {
    const bool success{m_window.create()};
    if (success) {
        m_window.show();
    }
    return success;
}

void Application::runMessageLoop() {
    MSG message{};
    // PostQuitMessage(0) makes `GetMessage` return zero result to stop the loop.
    while (GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
        m_director.draw();
        m_window.swapBuffers();
    }
}

} // namespace win
