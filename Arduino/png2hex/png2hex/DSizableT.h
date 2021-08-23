//DSizableT.h
#pragma once
#include "IDSizable.h"

template<typename T>
class DSizableT
    : public IDSizable<T>
{
public:
    T         width() const          override;
    T         height() const         override;
    void      width(const T)         override;
    void      height(const T)        override;
    void      size(const T, const T) override;
    void      size(const DSizeT<T>&) override;
    const DSizeT<T>& size() const    override;
protected:
    virtual void resize(DSizeT<T>&);
private:
    DSizeT<T> m_size;
};

template<typename T>
inline T DSizableT<T>::width() const
{
    return m_size.width();
}

template<typename T>
inline T DSizableT<T>::height() const
{
    return m_size.height();
}

template<typename T>
void DSizableT<T>::width(const T width)
{
    DSizeT<T> size(width, m_size.height());
    resize(size);
    m_size = size;
}

template<typename T>
void DSizableT<T>::height(const T height)
{
    DSizeT<T> size(m_size.width(), height);
    resize(size);
    m_size = size;
}

template<typename T>
void DSizableT<T>::size(const T width, const T height)
{
    DSizeT<T> size(width, height);
    resize(size);
    m_size = size;
}

template<typename T>
void DSizableT<T>::size(const DSizeT<T>& size)
{
    DSizeT<T> s = size;
    resize(s);
    m_size = s;
}

template<typename T>
inline const DSizeT<T>& DSizableT<T>::size() const
{
    return m_size;
}

template<typename T>
inline void DSizableT<T>::resize(DSizeT<T>&)
{}
