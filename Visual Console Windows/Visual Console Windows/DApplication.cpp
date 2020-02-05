//DApplication.cpp
#include "DApplication.h"
#include <Windows.h>

SystemEvents DApplication::events = SystemEvents();

DApplication::DApplication()
    : m_console()
    , m_consoleMessages()
    , m_systemMessages()
    , m_consoleLoop()
    , m_systemLoop()
    , m_drawLoop()
{
    m_console.setSize(80, 40);
    m_console.setFontSize(14);
    m_console.setTitle("Visual Console Windows");
}

void DApplication::run()
{
    m_consoleLoop.run([this]
        {
            consoleLoop();
        }, false);

    m_systemLoop.run([this]
        {
            systemLoop();
        }, false);

    m_drawLoop.run([this]
        {
            drawLoop();
        }, true);
}

void DApplication::exit()
{
    m_consoleLoop.stop();
    m_systemLoop.stop();
    m_drawLoop.stop();
}

void DApplication::consoleLoop()
{
    auto localCopyMessages = m_console.readMessages();

    for(auto msg : localCopyMessages)
    {
        DMessage message;
        message.type = msg.type;
        switch(msg.type)
        {
        case MessageType::KEY_UP:
        case MessageType::KEY_DOWN:
        {
            switch(m_keyStates ^ msg.keyStates)
            {
            case KeyState::NONE:
                switch(msg.data.key)
                {
                case Key::CTRL: message.data.key = m_keyStates & KeyState::CTRL_L ? Key::CTRL_L : Key::CTRL_R; break;
                case Key::ALT:  message.data.key = m_keyStates & KeyState::ALT_L ? Key::ALT_L : Key::ALT_R;  break;
                default:        message.data.key = msg.data.key;
                }
                break;
            case KeyState::ALT_L:  message.data.key = Key::ALT_L;  break;
            case KeyState::ALT_R:  message.data.key = Key::ALT_R;  break;
            case KeyState::CTRL_L: message.data.key = Key::CTRL_L; break;
            case KeyState::CTRL_R: message.data.key = Key::CTRL_R; break;
            default:               message.data.key = msg.data.key;
            }
            break;
        }
        case MessageType::MOUSE_DOUBLE_CLICK:
        case MessageType::MOUSE_BUTTONS:
        {
            byte button = m_mouseButtons ^ msg.data.byte;
            m_mouseButtons = msg.data.byte;
            if(MessageType::MOUSE_BUTTONS == msg.type)
            {
                message.type = m_mouseButtons & button ? MessageType::MOUSE_DOWN : MessageType::MOUSE_UP;
            }
            switch(button)
            {
            case MouseState::LEFT:    message.data.key = Key::MOUSE_L; break;
            case MouseState::RIGHT:   message.data.key = Key::MOUSE_R; break;
            case MouseState::MIDDLE1:
            case MouseState::MIDDLE2: message.data.key = Key::MOUSE_M; break;
            }
            break;
        }
        case MessageType::MOUSE_MOVE:
        {
            if(m_position != msg.data.position)
            {
                message.data.position = m_position = msg.data.position;
            }
            else
            {
                message.type = MessageType::NONE;
            }
            break;
        }
        case MessageType::MOUSE_WHEEL:
        {
            message.data.byte = msg.data.byte;
            break;
        }
        case MessageType::DISPLAY_RESIZE:
        {
            message.data.size = m_size = msg.data.size;
            break;
        }
        }

        if(MessageType::DISPLAY_RESIZE != msg.type)
        {
            m_keyStates = msg.keyStates;
        }
        message.keyStates = m_keyStates;

        if(MessageType::NONE != message.type)
        {
            m_systemMessages->push(message);
        }
    }
}

void DApplication::systemLoop()
{
    auto localCopyMessages = std::move(*m_systemMessages);

    for(auto message : localCopyMessages)
    {
        events.m_keyStates = message.keyStates;
        switch(message.type)
        {
        case MessageType::KEY_UP:
        {
            events.onKeyUp(message.data.key);
            break;
        }
        case MessageType::KEY_DOWN:
        {
            events.onKeyDown(message.data.key);
            break;
        }
        case MessageType::MOUSE_UP:
        {
            m_root.mouseUp(message.data.key);
            events.onMouseUp(message.data.key);
            break;
        }
        case MessageType::MOUSE_DOWN:
        {
            m_root.mouseDown(message.data.key);
            events.onMouseDown(message.data.key);
            break;
        }
        case MessageType::MOUSE_MOVE:
        {
            m_root.mouseMove(message.data.position);
            events.onMouseMove(message.data.position);
            break;
        }
        case MessageType::MOUSE_DOUBLE_CLICK:
        {
            m_root.mouseDown(message.data.key);
            events.onMouseDown(message.data.key);
            events.onMouseDoubleClick(message.data.key);
            break;
        }
        case MessageType::DISPLAY_RESIZE:
        {
            events.onDisplayResize(message.data.size);
            break;
        }
        }

        auto draw = m_drawBuffer->beginDraw();
        m_root.draw(draw);
        m_drawBuffer->endDraw();
    }
}

void DApplication::drawLoop()
{
}
