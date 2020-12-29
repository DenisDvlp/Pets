//DView.cpp
#include "DView.h"
#include <cstdarg>
#include <unordered_map>

void DView::subscribeSystemMessages(std::initializer_list<MessageType> types)
{
    subscriptionMessagHelper(types, true);
}

void DView::subscribeSystemMessages(MessageType type)
{
    subscriptionMessagHelper(type, true);
}

void DView::unsubscribeSystemMessages(std::initializer_list<MessageType> types)
{
    subscriptionMessagHelper(types, false);
}

void DView::unsubscribeSystemMessages(MessageType type)
{
    subscriptionMessagHelper(type, false);
}

void DView::onSystemMouseMove(const DPoint&)
{
}

void DView::subscriptionMessagHelper(std::initializer_list<MessageType> types, bool turn)
{
    for(auto type : types) {
         subscriptionMessagHelper(type, turn);
    }
}

void DView::subscriptionMessagHelper(MessageType type, bool turn)
{
    const static std::unordered_map<MessageType, byte> messageTypeShiftMap =
    {
        { MessageType::KEY_UP,             0 },
        { MessageType::KEY_DOWN,           1 },
        { MessageType::MOUSE_UP,           2 },
        { MessageType::MOUSE_DOWN,         3 },
        { MessageType::MOUSE_MOVE,         4 },
        { MessageType::MOUSE_DOUBLE_CLICK, 5 },
        { MessageType::MOUSE_WHEEL,        6 },
        { MessageType::DISPLAY_RESIZE,     7 },
    };

    auto shiftIt = messageTypeShiftMap.find(type);
    if(shiftIt != messageTypeShiftMap.end())
    {
        byte shift = 0;
        if (turn)
        {
            m_systemMessagesSubscription |= 1 << shiftIt->second;
        }
        else
        {
            m_systemMessagesSubscription &= 0 << shiftIt->second;
        }
    }
}
