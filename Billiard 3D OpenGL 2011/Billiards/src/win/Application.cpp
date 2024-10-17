#include "win/Application.hpp"

namespace win {

Application::Application(HINSTANCE hInstance)
    : m_window{L"billiard_main_window", L"Billiards by Denys Petrov 2024", hInstance}, m_messageLoop{[this] {
          m_scene.draw();
          m_window.swapBuffers();
      }} {}

void Application::run() {
    if (init()) {
        m_messageLoop.run();
    }
}

bool Application::init() {
    const bool success{m_window.create()};
    if (success) {
        m_window.show();
        m_square.position.z() = -3;
        m_scene.addSceneObject(m_square);
        m_scene.init();
        m_scene.resize(500, 500);
    }
    return success;
}

} // namespace win
