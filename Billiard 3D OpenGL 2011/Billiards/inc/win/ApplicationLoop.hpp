#pragma once
#include "Window.hpp"
#include "common/ThreadLoop.hpp"

namespace win {

class ApplicationLoop : public common::ThreadLoop {
  public:
    ApplicationLoop(Window& window);
    ~ApplicationLoop() override;

  public:
    void onStart() override;
    void onIteration() override;

  protected:
    Window& m_window;
};

} // namespace win
