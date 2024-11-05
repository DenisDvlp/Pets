#include "win/ApplicationLoop.hpp"
#include "common/Utils.hpp"

namespace win {

ApplicationLoop::ApplicationLoop(Window& window) : m_window{window} {}

ApplicationLoop::~ApplicationLoop() {
    wait();
}

void ApplicationLoop::onStart() {
    if (m_window.create()) {
        m_window.show();
    } else {
        stop();
    }
}

void ApplicationLoop::onIteration() {
    static MSG message{};
    //   PostQuitMessage(0) makes `GetMessage` return zero result to stop the loop.
    if (GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    } else {
        stop();
    }
}

} // namespace win
