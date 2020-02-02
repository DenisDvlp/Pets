//IMessageLoop.h
#pragma once
#include "ILoop.h"

class Message;
class IMessageReadable;

class IMessageLoop
    : public ILoop
{
public:
    IMessageLoop(IMessageReadable*);
    ~IMessageLoop() = default;
    void run(bool = false);
private:
    void loop() override;
    virtual void loop(Message) = 0;
private:
    IMessageReadable* const m_buffer;
};