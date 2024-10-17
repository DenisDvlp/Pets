#pragma once
#include <functional>

class MessageLoop final {
  public:
    MessageLoop(std::function<void()>);
    void run();

  private:
    std::function<void()> m_inLoopCallback{};
};
