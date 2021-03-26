#include "State.h"
#include <iostream>

void State::enter(State *parent)
{
    if (!m_entered)
    {
        std::cout << m_id << " open" << std::endl;
        m_parent = parent;
        m_entered = true;
        onEnter();
    }
}

void State::activate()
{
    if (m_entered && !m_activated)
    {
        std::cout << m_id << " activated" << std::endl;
        m_activated = true;
        onActivate();
    }
}

void State::deactivate()
{
    if (m_entered && m_activated)
    {
        std::cout << m_id << " deactivated" << std::endl;
        m_activated = false;
        onDeactivate();
    }
}

void State::exit()
{
    deactivate();
    if (m_entered)
    {
        std::cout << m_id << " close" << std::endl;
        m_parent = nullptr;
        m_entered = false;
        onExit();
    }
}

void State::registerID(int id)
{
    if (!isRegistered(id))
    {
        std::cout << id << " register" << std::endl;
        m_IDs.push_back(id);
    }
}

bool State::isRegistered(int id)
{
    return find(m_IDs.begin(), m_IDs.end(), id) != m_IDs.end();
}