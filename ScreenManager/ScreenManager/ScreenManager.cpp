#include "ScreenManager.h"
#include <iostream>
using std::cout;
using std::endl;

void ScreenManager::request(Message message)
{
    messages.push_back(message);
    if (messages.size() == 1)
    {
        handleMessages();
    }
}

void ScreenManager::handleMessages()
{
    Screen *prevOpened = lastOpened;
    while (messages.size() > 0)
    {
        switch (messages.front().type)
        {
        case Message::MSG_OPEN:
            openRequest(messages.front().id, messages.front().parentId);
            break;
        case Message::MSG_CLOSE:
            closeRequest(messages.front().id);
            break;
        default:;
        }
        messages.pop_front();
    }
    if (lastOpened != nullptr)
    {
        if (prevOpened != nullptr && prevOpened->m_id != lastOpened->m_id)
        {
            prevOpened->deactivate();
        }
        lastOpened->activate();
    }
}

void ScreenManager::openRequest(ScreenID id, ScreenID parentId)
{
    Screen *screen = get(id);
    Screen *parent = get(parentId);
    if (screen != nullptr)
    {
        screen->open(parent);
        lastOpened = screen;
    }
}

void ScreenManager::closeRequest(ScreenID id)
{
    Screen *screen = get(id);
    if (screen != nullptr)
    {
        Screen *s = screen;
        do {
            if (s->m_isActive)
            {
                lastOpened = screen->m_parent;
                break;
            }
            s = s->m_child;
        } while (s != nullptr && s->m_id != screen->m_id);
        screen->close();
    }
}

bool ScreenManager::has(ScreenID id)
{
    return screens.find(id) != screens.end();
}

Screen* ScreenManager::get(ScreenID id)
{
    return has(id) ? screens[id] : nullptr;
}

ScreenManager & ScreenManager::instance()
{
    static ScreenManager sm;
    return sm;
}

void ScreenManager::add(ScreenID id, Screen * screen)
{
    if (screen != nullptr && !has(id))
    {
        screen->m_id = id;
        screens[id] = screen;
    }
}

void ScreenManager::open(ScreenID id)
{
    open(1, id);
}

void ScreenManager::open(int count, ScreenID ids ...)
{
    bool startHandling = messages.size() == 0;
	ScreenID *id = &ids;
    for (int i = 0; i < count && has(id[i]); i++)
    {
        messages.push_back(Message(Message::MSG_OPEN, id[i], static_cast<ScreenID>(i == 0 ? -1 : id[i - 1])));
    }
    if (startHandling)
    {
        handleMessages();
    }
}

void ScreenManager::close(ScreenID id)
{
    request(Message(Message::MSG_CLOSE, id, static_cast<ScreenID>(-1)));
}

void ScreenManager::print()
{
    for (auto s : screens)
    {
        Screen *p = s.second->m_parent;
        Screen *c = s.second->m_child;
        cout << (!p ? 9 :  p->m_id) << " <-" << (s.second->m_isActive ? "(" : (s.second->m_isOpen ? "[" : " ")) << s.first << (s.second->m_isActive ? ")" : (s.second->m_isOpen ? "]" : " ")) << "-> " << (!c ? 9 : c->m_id) << endl;
    }
}
