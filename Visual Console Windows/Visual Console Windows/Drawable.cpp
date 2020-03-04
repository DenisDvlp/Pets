//Drawable.cpp
#include "Drawable.h"

Drawable::Drawable(Drawable* parent)
{
    setParent(parent);
}

Drawable::~Drawable()
{
    setParent(nullptr);
    for(auto child : m_children)
    {
        delete child;
    }
}

Drawable* Drawable::parent() const
{
    return m_parent;
}

void Drawable::setParent(Drawable* parent)
{
    if(m_parent)
    {
        m_parent->m_children.remove(this);
    }
    m_parent = parent;
    if(m_parent && m_parent->m_children.find(this) == m_parent->m_children.end())
    {
        m_parent->m_children.push(this);
    }
}

void Drawable::bringToFront()
{
    if(m_parent)
    {
        m_parent->m_children.remove(this);
        m_parent->m_children.push(this);
    }
}

void Drawable::sendToBack()
{
    if(m_parent)
    {
        m_parent->m_children.remove(this);
        m_parent->m_children.insert(0, this);
    }
}

/*void Drawable::draw(IDDraw* draw)
{
    onDraw(draw);
    for(auto child : m_children)
    {
        child->draw(draw);
    }
}*/

bool Drawable::mouseUp(Key key)
{
    auto result = false;
    auto size = m_children.size();
    for(decltype(size) i = 0; i < size; ++i)
    {
        result = m_children[size - i - 1]->mouseUp(key);
        if(result)
        {
            break;
        }
    }
    auto clicked = m_clicked;
    switch(key)
    {
    case Key::MOUSE_L: m_clicked &= ~0b001; break;
    case Key::MOUSE_R: m_clicked &= ~0b010; break;
    case Key::MOUSE_M: m_clicked &= ~0b100; break;
    }
    if(clicked != m_clicked)
    {
        onMouseUp(this, key);
        if(!result || m_rect.contains(m_mousePosition))
        {
            onClick(this, key);
            result = true;
        }
    }
    return result;
}

bool Drawable::mouseDown(Key key)
{
    auto result = false;
    auto size = m_children.size();
    for(decltype(size) i = 0; i < size; ++i)
    {
        result = m_children[size - i - 1]->mouseDown(key);
        if(result)
        {
            break;
        }
    }
    if(!result && m_rect.contains(m_mousePosition))
    {
        switch(key)
        {
        case Key::MOUSE_L: m_clicked |= 0b001; break;
        case Key::MOUSE_R: m_clicked |= 0b010; break;
        case Key::MOUSE_M: m_clicked |= 0b100; break;
        }
        onMouseDown(this, key);
        result = true;
    }
    return result;
}

bool Drawable::mouseMove(DPoint position)
{
    auto result = false;
    m_mousePosition = position;
    auto size = m_children.size();
    for(decltype(size) i = 0; i < size; ++i)
    {
        auto child = m_children[size - i - 1];
        if(!result && child->mouseMove(position))
        {
            result = true;
        }
        else if(child->m_isEntered)
        {
            child->m_isEntered = false;
            child->onMouseLeave(child);
        }
    }
    if(!result)
    {
        if(m_rect.contains(position))
        {
            result = true;
            onMouseMove(this, position);
            if(!m_isEntered)
            {
                m_isEntered = true;
                onMouseEnter(this);
            }
        }
    }
    else if(m_isEntered)
    {
        m_isEntered = false;
        onMouseLeave(this);
    }
    return result;
}

void Drawable::reshape(DRect& rect)
{
}

void Drawable::draw() const
{
}
