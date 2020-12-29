//DComposable.h
#pragma once
#include "DVector.h"
#ifdef _DEBUG
#include <assert.h>
#endif

template<typename T>
class DComposable
{
public:
    explicit DComposable(T* = nullptr);
    virtual ~DComposable();
    virtual void addChild(T*);
    virtual void removeChild(T*);
    void setParent(T*);
    void bringToFront();
    void sendToBack();
    const DVector<T*>& children() const;
    size_t childrenCount() const;
    T* parent() const;
protected:
    T* m_parent = nullptr;
    DVector<T*> m_children;
};

template<typename T>
DComposable<T>::DComposable(T* parent)
{
    setParent(parent);
}

template<typename T>
DComposable<T>::~DComposable()
{
    setParent(nullptr);

    for(auto child : m_children)
    {
        delete child;
    }
}

template<typename T>
void DComposable<T>::addChild(T* child)
{
    T* self = static_cast<T*>(this);
    if(child && child->m_parent != self)
    {
        child->setParent(self);
    }
}

template<typename T>
void DComposable<T>::removeChild(T* child)
{
    T* self = static_cast<T*>(this);
    if(child && child->m_parent == self)
    {
        m_children.remove(child);

        child->m_parent = nullptr;
    }
}

template<typename T>
void DComposable<T>::setParent(T* parent)
{
    if(m_parent != parent)
    {
        T* self = static_cast<T*>(this);
        //check parent loops
#ifdef _DEBUG
        if(parent)
        {
            auto next = parent;
            auto isChildAsParent = false;
            while(next)
            {
                if(self == next)
                {
                    isChildAsParent = true;
                    break;
                }
                next = next->m_parent;
            }
            if (isChildAsParent)
            {
              assert("You probably tried to set its child as a parent.");
            }
        }
#endif

        if(m_parent)
        {
            m_parent->m_children.remove(self);
        }

        if(parent)
        {
            parent->m_children.push(self);
        }

        m_parent = parent;
    }
}

template<typename T>
void DComposable<T>::bringToFront()
{
    if(m_parent)
    {
        T* self = static_cast<T*>(this);
        const auto isLast = !m_parent->m_children.empty() && m_parent->m_children.last() == self;

        if(!isLast)
        {
            m_parent->m_children.remove(self);
            m_parent->m_children.push(self);
        }
    }
}

template<typename T>
void DComposable<T>::sendToBack()
{
    if(m_parent)
    {
        T* self = static_cast<T*>(this);
        const auto isFisrt = !m_parent->m_children.empty() && m_parent->m_children.first() == self;

        if(!isFisrt)
        {
            m_parent->m_children.remove(self);
            m_parent->m_children.front(self);
        }
    }
}

template<typename T>
const DVector<T*>& DComposable<T>::children() const
{
    return m_children;
}

template<typename T>
inline size_t DComposable<T>::childrenCount() const
{
    return m_children.size();
}

template<typename T>
inline T* DComposable<T>::parent() const
{
    return m_parent;
}
