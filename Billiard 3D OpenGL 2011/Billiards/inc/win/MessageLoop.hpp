#pragma once
#include <functional>

namespace win {

class MessageLoop final {
  public:
    MessageLoop(std::function<void()>);
    void run();

  private:
    std::function<void()> m_inLoopCallback{};
};

} // namespace win
