//SizableT.h
#pragma once
#include "ISizable.h"
#include "Size.h"

template<typename T>
class SizableT
    : public ISizable<T>
{
public:
    T width() const       override;
    T height() const      override;
    void width(T)         override;
    void height(T)        override;
    void size(T, T)       override;
    void size(SizeT<T>)   override;
    SizeT<T> size() const override;
private:
    virtual void resize(SizeT<T>&) = 0;
protected:
    SizeT<T> m_size;
};

template<typename T>
inline T SizableT<T>::width() const
{
    return m_size.width();
}

template<typename T>
inline T SizableT<T>::height() const
{
    return m_size.height();
}

template<typename T>
void SizableT<T>::width(T width)
{
    SizeT<T> size(width, m_size.height());
    resize(size);
    m_size = size;
}

template<typename T>
void SizableT<T>::height(T height)
{
    SizeT<T> size(m_size.width(), height);
    resize(size);
    m_size = size;
}

template<typename T>
void SizableT<T>::size(T width, T height)
{
    SizeT<T> size(width, height);
    resize(size);
    m_size = size;
}

template<typename T>
void SizableT<T>::size(SizeT<T> size)
{
    resize(size);
    m_size = size;
}

template<typename T>
inline SizeT<T> SizableT<T>::size() const
{
    return m_size;
}