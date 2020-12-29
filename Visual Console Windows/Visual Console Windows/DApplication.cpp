//DApplication.cpp
#include "DApplication.h"
#include "KeyState.h"
#include "MouseState.h"
#include "Utils.h"

DApplication::DApplication()
    : m_console()
    , m_consoleMessages()
    , m_systemMessages()
    , m_consoleLoop()
    , m_systemLoop()
    , m_drawLoop()
{
    m_console.size(80, 40);
    m_console.fontSize(14);
    m_console.title("Visual Console Windows");

    m_drawBuffer->size(80, 40);
    m_rootView.position(10, 7);
    m_rootView.size(10, 7);
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

void DApplication::addView(DView* view)
{
  m_rootView.addChild(view);
}

void DApplication::consoleLoop()
{
    auto messages = m_console.recentMessages();

    DMessage message;

    for(auto msg : messages)
    {
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

    utils::sleep(10);
}

void DApplication::systemLoop()
{
    DVector<DMessage> messages;

    {
        auto locked_messages = m_systemMessages.getLocked();
        messages = std::move(*locked_messages);
    }

    for(auto msg : messages)
    {
        switch(msg.type)
        {
        case MessageType::KEY_UP:
        {
            break;
        }
        case MessageType::KEY_DOWN:
        {
            break;
        }
        case MessageType::MOUSE_UP:
        {
            break;
        }
        case MessageType::MOUSE_DOWN:
        {
            break;
        }
        case MessageType::MOUSE_MOVE:
        {
            for (auto child : m_rootView.children())
            {
                child->onSystemMouseMove(msg.data.position);
            }
            break;
        }
        case MessageType::MOUSE_DOUBLE_CLICK:
        {
            break;
        }
        case MessageType::DISPLAY_RESIZE:
        {
            break;
        }
        }
    }

    auto* draw = m_drawBuffer->beginWrite();
    if(draw)
    {
        draw->fill(DColors::GRAY);
        drawRoot(*draw, m_rootView);
        m_drawBuffer->endWrite(draw);
    }
    utils::sleep(10);
}

void DApplication::drawLoop()
{
    const auto* draw = m_drawBuffer->beginRead();
    if(draw)
    {
        m_console.show(draw->raw());
        m_drawBuffer->endRead(draw);
    }

    utils::sleep(10);
}

void DApplication::drawRoot(IDDraw& draw, DView& parent)
{
    parent.draw(draw);
    for (auto child : parent.children())
    {
        drawRoot(draw, *child);
    }
}
