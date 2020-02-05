//DLoop.cpp
#include "DLoop.h"
#include "DSfinae.h"
#include <thread>

template<typename LoopFunc>
void DLoop::run(LoopFunc loopFunc, bool sync)
{
    static_assert(is_callable_match<LoopFunc, void>, "LoopFunc shall match 'void function()'");

    if(!m_isRunning)
    {
        m_isRunning = true;
        auto thread = std::thread([this]
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

void DLoop::stop()
{
    m_isRunning = false;
}
