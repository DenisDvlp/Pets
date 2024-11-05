#pragma once
#include <atomic>
#include <mutex>
#include <thread>

namespace common {

class ThreadLoop {
  public:
    virtual ~ThreadLoop() = default;
    void run();
    void stop();
    bool isRunning() const;
    void wait();

  protected:
    virtual void onStart();
    virtual void onIteration();
    virtual void onStop();

  protected:
    std::atomic_bool m_isRunning{};
    std::thread m_threadLoop{};
    std::once_flag m_once_flag{};
};

} // namespace common
