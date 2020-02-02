#pragma once
#include "IPositionable.h"
#include "Point.h"

template<typename T>
class PositionableT
    : public IPositionable<T>
{
public:
    T x() const                override;
    T y() const                override;
    void x(T)                  override;
    void y(T)                  override;
    void position(T, T)        override;
    void position(PointT<T>)   override;
    PointT<T> position() const override;
private:
    virtual void reposition(PointT<T>&) = 0;
protected:
    PointT<T> m_position;
};

template<typename T>
T PositionableT<T>::x() const
{
    return m_position.x();
}

template<typename T>
T PositionableT<T>::y() const
{
    return m_position.y();
}

template<typename T>
void PositionableT<T>::x(T x)
{
    PointT<T> position(x, m_position.y());
    reposition(position);
    m_position = position;
}

template<typename T>
void PositionableT<T>::y(T y)
{
    PointT<T> position(m_position.x(), y);
    reposition(position);
    m_position = position;
}

template<typename T>
void PositionableT<T>::position(T x, T y)
{
    PointT<T> position(x, y);
    reposition(position);
    m_position = position;
}

template<typename T>
void PositionableT<T>::position(PointT<T> position)
{
    reposition(position);
    m_position = position;
}

template<typename T>
PointT<T> PositionableT<T>::position() const
{
    return m_position;
}