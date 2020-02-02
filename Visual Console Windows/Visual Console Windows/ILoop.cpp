//ILoop.cpp
#include "ILoop.h"
#include <thread>

void ILoop::run(bool sync/*= false*/)
{
    if(!m_isRunning)
    {
        m_isRunning = true;
        auto thread = std::thread([this]
            {
                while(m_isRunning)
                {
                    loop();
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

void ILoop::stop()
{
    m_isRunning = false;
}
