#include "core/Application.hpp"

namespace core {

Application::Application(HINSTANCE hInstance)
    : m_director{}, m_mainWindow{hInstance, m_director}, m_applicationLoop{m_mainWindow} {
    m_applicationLoop.run();
}

} // namespace core
