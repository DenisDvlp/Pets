#include "core/RenderingLoop.hpp"
#include "core/MainWindow.hpp"

namespace core {

RenderingLoop::RenderingLoop(MainWindow& mainWindow, gl::Director& director)
    : m_mainWindow{mainWindow}, m_director{director} {}

RenderingLoop::~RenderingLoop() {
    wait();
}

void RenderingLoop::onStart() {
    m_mainWindow.createOpenGlRenderingContext();
    m_director.init();
}

void RenderingLoop::onIteration() {
    m_director.adjust();
    m_director.action();
    m_mainWindow.swapBuffers();
}

void RenderingLoop::onStop() {
    m_mainWindow.destroyOpenGlRenderingContext();
}

} // namespace core
