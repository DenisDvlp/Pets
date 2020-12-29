//DView.h
#pragma once
#include "DComposable.h"
#include "DShapeable.h"
#include "DDrawable.h"
#include "DDrawable.h"
#include "MessageType.h"

class DView
    : public DComposable<DView>
    , public DShapeable
    , public DDrawable
{
public:
    using DComposable<DView>::DComposable;
    virtual void onSystemMouseMove(const DPoint&);
protected:
    void subscribeSystemMessages(std::initializer_list<MessageType>);
    void subscribeSystemMessages(MessageType);
    void unsubscribeSystemMessages(std::initializer_list<MessageType>);
    void unsubscribeSystemMessages(MessageType);
private:
    void subscriptionMessagHelper(std::initializer_list<MessageType>, bool turn);
    void subscriptionMessagHelper(MessageType, bool turn);
private:
    byte m_systemMessagesSubscription = 0;
};

