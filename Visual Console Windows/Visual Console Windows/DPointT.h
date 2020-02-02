//DPointT.h
#pragma once
#include <cmath>

template<typename T>
class DPointT
{
public:
    DPointT() = default;
    DPointT(const T, const T);

    void set(const T, const T);

    void inc(const T, const T);
    void incX(const T);
    void incY(const T);

    T    x() const;
    void x(const T);
    T    y() const;
    void y(const T);

    bool isZero() const;
    double distance(const DPointT&) const;

    bool operator==(const DPointT&) const;
    bool operator!=(const DPointT&) const;
    bool operator> (const DPointT&) const;
    bool operator< (const DPointT&) const;
    bool operator>=(const DPointT&) const;
    bool operator<=(const DPointT&) const;
    DPointT operator+ (const DPointT&) const;
    DPointT operator- (const DPointT&) const;
    DPointT operator+ () const;
    DPointT operator- () const;
    DPointT& operator+=(const DPointT&);
    DPointT& operator-=(const DPointT&);

private:
    T m_x = 0;
    T m_y = 0;
};

////////////////impementation////////////////

template<typename T>
DPointT<T>::DPointT(const T x, const T y) 
   : m_x(x)
   , m_y(y)
{}

template<typename T>
void DPointT<T>::set(const T x, const T y)
{
    m_x = x;
    m_y = y;
}

template<typename T>
void DPointT<T>::inc(const T x, const T y)
{
    m_x += x;
    m_y += y;
}

template<typename T>
inline void DPointT<T>::incX(const T x)
{
    m_x += x;
}

template<typename T>
inline void DPointT<T>::incY(const T y)
{
    m_y += y;
}

template<typename T>
inline T DPointT<T>::x() const
{
    return m_x;
}

template<typename T>
inline void DPointT<T>::x(const T x)
{
    m_x = x;
}

template<typename T>
inline T DPointT<T>::y() const
{
    return m_y;
}

template<typename T>
inline void DPointT<T>::y(const T y)
{
    m_y = y;
}

template<typename T>
bool DPointT<T>::isZero() const
{
    return !(m_x | m_y);
}

template<typename T>
double DPointT<T>::distance(const DPointT& point) const
{
    T x1 = m_x;
    T x2 = point.m_x;
    T y1 = m_y;
    T y2 = point.m_y;
    normalize(x1, x2);
    normalize(y1, y2);
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

template<typename T>
bool DPointT<T>::operator==(const DPointT& point) const
{
    return m_x == point.m_x && m_y == point.m_y;
}

template<typename T>
bool DPointT<T>::operator!=(const DPointT& point) const
{
    return !operator==(point);
}

template<typename T>
bool DPointT<T>::operator>(const DPointT& point) const
{
    return !operator<=(point);
}

template<typename T>
bool DPointT<T>::operator<(const DPointT& point) const
{
    return !operator>=(point);
}

template<typename T>
bool DPointT<T>::operator>=(const DPointT& point) const
{
    return m_x >= point.m_x && m_y >= point.m_y;
}

template<typename T>
bool DPointT<T>::operator<=(const DPointT& point) const
{
    return m_x <= point.m_x && m_y <= point.m_y;
}

template<typename T>
DPointT<T> DPointT<T>::operator+(const DPointT& point) const
{
    return DPointT(m_x + point.m_x, m_y + point.m_y);
}

template<typename T>
DPointT<T> DPointT<T>::operator-(const DPointT& point) const
{
    return DPointT(m_x - point.m_x, m_y - point.m_y);
}

template<typename T>
DPointT<T> DPointT<T>::operator+() const
{
    return DPointT(m_x, m_y);
}

template<typename T>
DPointT<T> DPointT<T>::operator-() const
{
    return DPointT(-m_x, -m_y);
}

template<typename T>
DPointT<T>& DPointT<T>::operator+=(const DPointT& point)
{
    shift(point);
    return *this;
}

template<typename T>
DPointT<T>& DPointT<T>::operator-=(const DPointT& point)
{
    shift(-point);
    return *this;
}