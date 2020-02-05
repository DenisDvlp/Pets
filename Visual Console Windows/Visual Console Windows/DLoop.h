//DLoop.h
#pragma once
#include <atomic>

class DLoop
{
public:
    template<typename LoopFunc>
    void run(LoopFunc, bool);
    void stop();
private:
    std::atomic_bool m_isRunning = false;
};