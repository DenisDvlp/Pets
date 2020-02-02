//SystemLoop.cpp
#include "SystemLoop.h"
#include "BasicTypes.h"
#include "SystemEvents.h"
#include "IDrawBuffer.h"
#include "Utils.h"
#include <iostream>

SystemLoop::SystemLoop(IMessageReadable* buffer, SystemEvents* systemEvents, IDrawBuffer* drawBuffer, Drawable* drawable)
    : IMessageLoop(buffer)
    , m_systemEvents(systemEvents)
    , m_drawBuffer(drawBuffer)
    , m_rootDrawable(drawable)
{
}

void SystemLoop::loop(Message message)
{
    m_systemEvents->m_keyStates = message.keyStates;
    switch(message.type)
    {
    case MessageType::KEY_UP:
    {
        m_systemEvents->onKeyUp(message.data.key);
        break;
    }
    case MessageType::KEY_DOWN:
    {
        m_systemEvents->onKeyDown(message.data.key);
        break;
    }
    case MessageType::MOUSE_UP:
    {
        m_rootDrawable->mouseUp(message.data.key);
        m_systemEvents->onMouseUp(message.data.key);
        break;
    }
    case MessageType::MOUSE_DOWN:
    {
        m_rootDrawable->mouseDown(message.data.key);
        m_systemEvents->onMouseDown(message.data.key);
        break;
    }
    case MessageType::MOUSE_MOVE:
    {
        m_rootDrawable->mouseMove(message.data.position);
        m_systemEvents->onMouseMove(message.data.position);
        break;
    }
    case MessageType::MOUSE_DOUBLE_CLICK:
    {
        m_rootDrawable->mouseDown(message.data.key);
        m_systemEvents->onMouseDown(message.data.key);
        m_systemEvents->onMouseDoubleClick(message.data.key);
        break;
    }
    case MessageType::DISPLAY_RESIZE:
    {
        m_systemEvents->onDisplayResize(message.data.size);
        break;
    }
    }

    auto draw = m_drawBuffer->beginDraw();
    m_rootDrawable->draw(draw);
    m_drawBuffer->endDraw();
}