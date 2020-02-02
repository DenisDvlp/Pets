//IMessageLoop.cpp
#include "IMessageLoop.h"
#include "BasicTypes.h"
#include "IMessageReadable.h"
#include "Utils.h"

IMessageLoop::IMessageLoop(IMessageReadable* buffer)
    : m_buffer(buffer)
{
}

void IMessageLoop::run(bool sync/*= false*/)
{
    if(m_buffer)
    {
        ILoop::run(sync);
    }
}

void IMessageLoop::loop()
{
    auto messages = m_buffer->readMessages();

    for(auto message : messages)
    {
        loop(message);
    }

    utils::sleep(1);
}
