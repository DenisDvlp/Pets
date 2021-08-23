//PointBase.h
#pragma once

template<typename T>
class PointBase
{
  T m_x = 0;
  T m_y = 0;

public:

  PointBase();
  PointBase(T x, T y);

  void        set(T x, T y);
  void        shift(T dx, T dy);

  T           x();
  void        x(T x);
  T           y();
  void        y(T y);

  bool        isZero();
  double      distance(PointBase<T> point);

  bool        operator==(PointBase<T> point);
  bool        operator!=(PointBase<T> point);
  bool        operator> (PointBase<T> point);
  bool        operator< (PointBase<T> point);
  bool        operator>=(PointBase<T> point);
  bool        operator<=(PointBase<T> point);
  PointBase   operator+ (PointBase<T> point);
  PointBase   operator- (PointBase<T> point);
  PointBase&  operator+=(PointBase<T> point);
  PointBase&  operator-=(PointBase<T> point);
};

////////////////impementation////////////////

template<typename T>
PointBase<T>::PointBase() {}

template<typename T>
PointBase<T>::PointBase(T x, T y) :
  m_x(x),
  m_y(y)
{}

template<typename T>
inline void PointBase<T>::set(T x, T y)
{
  m_x = x;
  m_y = y;
}

template<typename T>
void PointBase<T>::shift(T x, T y)
{
  m_x += x;
  m_y += y;
}

template<typename T>
inline T PointBase<T>::x()
{
  return m_x;
}

template<typename T>
inline void PointBase<T>::x(T x)
{
  m_x = x;
}

template<typename T>
inline T PointBase<T>::y()
{
  return m_y;
}

template<typename T>
inline void PointBase<T>::y(T y)
{
  m_y = y;
}

template<typename T>
bool PointBase<T>::isZero()
{
  return !(m_x | m_y);
}

template<typename T>
double PointBase<T>::distance(PointBase<T> point)
{
  return sqrt(pow(m_x - point.m_x, 2) + pow(m_y - point.m_y, 2));
}

template<typename T>
bool PointBase<T>::operator==(PointBase<T> point)
{
  return m_x == point.m_x && m_y == point.m_y;
}

template<typename T>
bool PointBase<T>::operator!=(PointBase<T> point)
{
  return !(*this == point);
}

template<typename T>
inline bool PointBase<T>::operator>(PointBase<T> point)
{
  return
    m_x >= point.m_x && m_y >  point.m_y ||
    m_x >  point.m_x && m_y >= point.m_y;
}

template<typename T>
inline bool PointBase<T>::operator<(PointBase<T> point)
{
  return
    m_x <= point.m_x && m_y <  point.m_y ||
    m_x <  point.m_x && m_y <= point.m_y;
}

template<typename T>
inline bool PointBase<T>::operator>=(PointBase<T> point)
{
  return *this > point || *this == point;
}

template<typename T>
inline bool PointBase<T>::operator<=(PointBase<T> point)
{
  return *this < point || *this == point;
}

template<typename T>
inline PointBase<T> PointBase<T>::operator+(PointBase<T> point)
{
  return PointBase(m_x + point.m_x, m_y + point.m_y);
}

template<typename T>
inline PointBase<T> PointBase<T>::operator-(PointBase<T> point)
{
  return PointBase(m_x - point.m_x, m_y - point.m_y);
}

template<typename T>
PointBase<T> & PointBase<T>::operator+=(PointBase<T> point)
{
  m_x += point.m_x;
  m_y += point.m_y;
  return *this;
}

template<typename T>
PointBase<T> & PointBase<T>::operator-=(PointBase<T> point)
{
  m_x -= point.m_x;
  m_y -= point.m_y;
  return *this;
}