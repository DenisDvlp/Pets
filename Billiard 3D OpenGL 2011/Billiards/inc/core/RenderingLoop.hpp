#pragma once
#include "common/ThreadLoop.hpp"
#include "graphics/Director.hpp"

namespace core {

class MainWindow;

class RenderingLoop final : public common::ThreadLoop {
  public:
    RenderingLoop(MainWindow& mainWindow, gl::Director& director);
    ~RenderingLoop();

  private:
    void onStart() override;
    void onIteration() override;
    void onStop() override;

  private:
    MainWindow& m_mainWindow;
    gl::Director& m_director;
};

} // namespace core
