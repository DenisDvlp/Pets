//DLoop.h
#pragma once
#include "DSfinae.h"
#include <atomic>
#include <thread>

class DLoop
{
public:
    template<typename LoopFunc>
    void run(LoopFunc, bool);
    void stop();
private:
    std::atomic_bool m_isRunning = false;
};

template<typename LoopFunc>
void DLoop::run(LoopFunc loopFunc, bool sync)
{
    static_assert(is_callable_match<LoopFunc, void>, "LoopFunc shall match 'void function()'");

    if(!m_isRunning)
    {
        m_isRunning = true;
        auto thread = std::thread([this, loopFunc]
            {
                while(m_isRunning)
                {
                    loopFunc();
                }
            });

        if(sync)
        {
            thread.join();
        }
        else
        {
            thread.detach();
        }
    }
}