//ILoop.h
#pragma once
#include <atomic>

class ILoop
{
public:
    virtual ~ILoop() = default;
    void run(bool sync = false);
    void stop();
private:
    virtual void loop() = 0;
private:
    std::atomic_bool m_isRunning = false;
};

