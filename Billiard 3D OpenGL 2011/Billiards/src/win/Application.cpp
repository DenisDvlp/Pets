#include "win/Application.hpp"

namespace win {

Application::Application(HINSTANCE hInstance)
    : m_window{L"billiard_main_window", L"Billiards by Denys Petrov 2024", hInstance} {}

void Application::run() {
    if (init()) {
        runMessageLoop();
    }
}

bool Application::init() {
    const bool success{m_window.create()};
    if (success) {
        m_window.show();
        m_square.position.z() = -1;
        m_scene.addActor(m_light);
        m_scene.addActor(m_square);
        m_scene.init();
        m_scene.resize(500, 500);
    }
    return success;
}

void Application::runMessageLoop() {
    MSG message{};
    // PostQuitMessage(0) makes `GetMessage` return zero result to stop the loop.
    while (GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
        m_scene.draw();
        m_window.swapBuffers();
    }
}

} // namespace win
