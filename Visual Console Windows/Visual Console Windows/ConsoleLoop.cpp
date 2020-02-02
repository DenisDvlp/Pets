//ConsoleLoop.cpp
#include "ConsoleLoop.h"
#include "MessageBuffer.h"

ConsoleLoop::ConsoleLoop(IMessageReadable* buffer, MessageBuffer* messageBuffer)
    : IMessageLoop(buffer)
    , m_messageBuffer(messageBuffer)
{
}

void ConsoleLoop::loop(Message msg)
{
    Message message;
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
        m_messageBuffer->addMessage(message);
    }
}