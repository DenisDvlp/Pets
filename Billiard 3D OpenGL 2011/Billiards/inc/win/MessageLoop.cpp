#include "MessageLoop.hpp"
#include "Windows.hpp"

MessageLoop::MessageLoop(std::function<void()> inLoopCallback) : m_inLoopCallback{std::move(inLoopCallback)} {}

void MessageLoop::run() {
    MSG message{};
    // PostQuitMessage(0) makes `GetMessage` return zero result to stop the loop.
    while (GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
        m_inLoopCallback();
    }
}
