#include "Application.hpp"

Application::Application(HINSTANCE hInstance)
    : m_window{L"main_window", L"Billiards by Denys Petrov 2024", hInstance} {}

void Application::run() {
    if (!m_window.create()) {
        return;
    }
    m_window.show();
    MSG message{};
    while (GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

Application::~Application() {}
