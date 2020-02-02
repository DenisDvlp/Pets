#include "DComposable.h"
#ifdef _DEBUG
#include <assert.h>
#endif

DComposable::DComposable(DComposable* parent)
{
    setParent(parent);
}

DComposable::~DComposable()
{
    setParent(nullptr);

    for(auto child : m_children)
    {
        delete child;
    }
}

void DComposable::addChild(DComposable* child)
{
    if(child && child->m_parent != this)
    {
        child->setParent(this);
    }
}

void DComposable::removeChild(DComposable* child)
{
    if(child && child->m_parent == this)
    {
        m_children.remove(child);

        child->m_parent = nullptr;
    }
}

void DComposable::setParent(DComposable* parent)
{
    if(m_parent != parent)
    {

        //check parent loops
#ifdef _DEBUG
        if(parent)
        {
            auto next = parent;
            while(next)
            {
                assert(this != next, "You probably tried to set its child as a parent.");
                next = next->m_parent;
            }
        }
#endif

        if(m_parent)
        {
            m_parent->m_children.remove(this);
        }

        if(parent)
        {
            parent->m_children.push(this);
        }

        m_parent = parent;
    }
}

void DComposable::bringToFront()
{
    if(m_parent)
    {
        const auto isLast = !m_parent->m_children.empty() && m_parent->m_children.last() == this;

        if(!isLast)
        {
            m_parent->m_children.remove(this);
            m_parent->m_children.push(this);
        }
    }
}

void DComposable::sendToBack()
{
    if(m_parent)
    {
        const auto isFisrt = !m_parent->m_children.empty() && m_parent->m_children.first() == this;

        if(!isFisrt)
        {
            m_parent->m_children.remove(this);
            m_parent->m_children.front(this);
        }
    }
}

inline const DVector<DComposable*>& DComposable::children()
{
    return m_children;
}

inline size_t DComposable::childrenCount()
{
    return m_children.size();
}

inline DComposable* DComposable::parent()
{
    return m_parent;
}
