#include "Screen.h"
#include <iostream>
using std::cout;
using std::endl;

void Screen::open(Screen * parent)
{
    if (!m_isOpen)
    {
        m_isOpen = true;

        if (parent != nullptr)
        {
            if (parent->m_child != nullptr)
            {
                parent->m_child->close();
            }
            parent->m_child = this;
        }
        m_parent = parent;

        cout << m_id << " open" << endl;
        onOpen();
    }
}

void Screen::close()
{
    deactivate();
    if (m_isOpen)
    {
        m_isOpen = false;

        if (m_parent != nullptr)
        {
            m_parent->m_child = nullptr;
        }
        m_parent = nullptr;

        if (m_child != nullptr)
        {
            m_child->close();
        }
        m_child = nullptr;

        cout << m_id << " close" << endl;
        onClose();
    }
}

void Screen::activate()
{
    if (m_isOpen && !m_isActive)
    {
        cout << m_id << " activated" << endl;
        m_isActive = true;
        onActivate();
    }
}

void Screen::deactivate()
{
    if (m_isOpen && m_isActive)
    {
        std::cout << m_id << " deactivated" << std::endl;
        m_isActive = false;
        onDeactivate();
    }
}

void Screen::action()
{
    if (m_isOpen && m_isActive)
    {
        std::cout << m_id << " action" << std::endl;
        onAction();
    }
}

ScreenID Screen::id()
{
    return m_id;
}

Screen * Screen::parent()
{
    return m_parent;
}

Screen * Screen::child()
{
    return m_child;
}

bool Screen::isActive()
{
    return m_isActive;
}
