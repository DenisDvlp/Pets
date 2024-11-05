#include "common/ThreadLoop.hpp"
#include "common/Utils.hpp"

namespace common {

void ThreadLoop::run() {
    if (!m_isRunning.exchange(true)) {
        m_threadLoop = std::thread{[this]() {
            onStart();
            while (m_isRunning) {
                onIteration();
            }
            onStop();
        }};
    }
}

void ThreadLoop::stop() {
    m_isRunning.store(false);
}

bool ThreadLoop::isRunning() const {
    return m_isRunning.load();
}

void ThreadLoop::wait() {
    std::call_once(m_once_flag, [this] { m_threadLoop.join(); });
}

void ThreadLoop::onStart() {}

void ThreadLoop::onIteration() {}

void ThreadLoop::onStop() {}

} // namespace common
