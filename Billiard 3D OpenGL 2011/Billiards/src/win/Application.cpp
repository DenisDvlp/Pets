#include "win/Application.hpp"

Application::Application(HINSTANCE hInstance)
    : m_window{L"billiard_main_window", L"Billiards by Denys Petrov 2024", hInstance} {}

void Application::run() {
    if (m_window.create()) {
        m_window.show();
        m_square.position.z() = -3;
        m_scene.addSceneObject(m_square);
        m_scene.init();
        m_scene.resize(500, 500);
        runMessageLoop();
    }
}

void Application::runMessageLoop() {
    MSG message{};
    // PostQuitMessage(0) makes `GetMessage` return zero result to stop the loop.
    while (GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
        m_scene.draw();
        SwapBuffers(m_window.m_handleDeviceContext);
    }
}

Application::~Application() {}
