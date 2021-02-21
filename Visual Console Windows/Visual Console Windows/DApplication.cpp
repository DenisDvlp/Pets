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
          message.data.key = msg.data.key;
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
                message.data.position = msg.data.position;
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

    m_systemMessages.moveTo(messages);

    for(auto msg : messages)
    {
        m_cachedMessage = msg;
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
            onSystemMouseUp();
            break;
        }
        case MessageType::MOUSE_DOWN:
        {
            onSystemMouseDown();
            break;
        }
        case MessageType::MOUSE_MOVE:
        {
            onSystemMouseMove();
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
        case MessageType::APP_FOCUS:
        {
            break;
        }
        }
    }

    auto* draw = m_drawBuffer->beginWrite();
    if(draw)
    {
        draw->fill(DColors::GRAY);
        drawRoot(m_rootView, *draw);
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

void DApplication::drawRoot(DView& parent, IDDraw& draw)
{
    parent.draw(draw);
    for (auto child : parent.children())
    {
        drawRoot(*child, draw);
    }
}

bool DApplication::onSystemMouseEvent(DView& parent, const MouseCallback& callback)
{
  auto& children = parent.children();
  bool handled = false;

  for (auto b = children.rbegin(), e = children.rend(); !handled && b != e; ++b)
  {
    handled = onSystemMouseEvent(**b, callback);
  }

  if (!handled && parent.rect().contains(m_cachedMessage.data.position))
  {
    handled = true;
    callback(parent, { m_cachedMessage.data.key, m_cachedMessage.data.position });
  }

  return handled;
}

bool DApplication::onSystemMouseUp()
{
  auto callback = [](DView& parent, const DMouseMessage& msg)
  {
    parent.onSystemMouseUp(msg);
  };
  return onSystemMouseEvent(m_rootView, callback);
}

bool DApplication::onSystemMouseDown()
{
  auto callback = [](DView& parent, const DMouseMessage& msg)
  {
    parent.onSystemMouseDown(msg);
  };
  return onSystemMouseEvent(m_rootView, callback);
}

bool DApplication::onSystemMouseMove()
{
  auto callback = [](DView& parent, const DMouseMessage& msg)
  {
      parent.onSystemMouseMove(msg);
  };
  return onSystemMouseEvent(m_rootView, callback);
}
