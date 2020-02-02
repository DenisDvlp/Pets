#pragma once
#include "IDPositionable.h"

template<typename T>
class DPositionableT
    : public IDPositionable<T>
{
public:
    T          x() const                   override;
    T          y() const                   override;
    void       x(const T)                  override;
    void       y(const T)                  override;
    void       position(const T, const T)  override;
    void       position(const DPointT<T>&) override;
    DPointT<T> position() const            override;
protected:
    virtual void reposition(DPointT<T>&);
private:
    DPointT<T> m_position;
};

template<typename T>
inline T DPositionableT<T>::x() const
{
    return m_position.x();
}

template<typename T>
inline T DPositionableT<T>::y() const
{
    return m_position.y();
}

template<typename T>
void DPositionableT<T>::x(const T x)
{
    DPointT<T> position(x, m_position.y());
    reposition(position);
    m_position = position;
}

template<typename T>
void DPositionableT<T>::y(const T y)
{
    DPointT<T> position(m_position.x(), y);
    reposition(position);
    m_position = position;
}

template<typename T>
void DPositionableT<T>::position(const T x, const T y)
{
    DPointT<T> position(x, y);
    reposition(position);
    m_position = position;
}

template<typename T>
void DPositionableT<T>::position(const DPointT<T>& position)
{
    DPointT<T> p = position;
    reposition(p);
    m_position = p;
}

template<typename T>
inline DPointT<T> DPositionableT<T>::position() const
{
    return m_position;
}

template<typename T>
inline void DPositionableT<T>::reposition(DPointT<T>&)
{}
