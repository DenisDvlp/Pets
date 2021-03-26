#pragma once

template<typename T>
class CPointBase
{
  T m_x = 0;
  T m_y = 0;

public:

  CPointBase();
  CPointBase(T x, T y);

  void        set(T x, T y);
  void        shift(T dx, T dy);

  T           x();
  void        x(T x);
  T           y();
  void        y(T y);

  bool        isZero();
  double      distance(CPointBase<T> point);

  bool        operator==(CPointBase<T> point);
  bool        operator!=(CPointBase<T> point);
  bool        operator> (CPointBase<T> point);
  bool        operator< (CPointBase<T> point);
  bool        operator>=(CPointBase<T> point);
  bool        operator<=(CPointBase<T> point);
  CPointBase  operator+ (CPointBase<T> point);
  CPointBase  operator- (CPointBase<T> point);
  CPointBase& operator+=(CPointBase<T> point);
  CPointBase& operator-=(CPointBase<T> point);
};

////////////////impementation////////////////

template<typename T>
CPointBase<T>::CPointBase() {}

template<typename T>
CPointBase<T>::CPointBase(T x, T y) :
  m_x(x),
  m_y(y)
{}

template<typename T>
inline void CPointBase<T>::set(T x, T y)
{
  m_x = x;
  m_y = y;
}

template<typename T>
void CPointBase<T>::shift(T x, T y)
{
  m_x += x;
  m_y += y;
}

template<typename T>
inline T CPointBase<T>::x()
{
  return m_x;
}

template<typename T>
inline void CPointBase<T>::x(T x)
{
  m_x = x;
}

template<typename T>
inline T CPointBase<T>::y()
{
  return m_y;
}

template<typename T>
inline void CPointBase<T>::y(T y)
{
  m_y = y;
}

template<typename T>
bool CPointBase<T>::isZero()
{
  return !(m_x | m_y);
}

template<typename T>
double CPointBase<T>::distance(CPointBase<T> point)
{
  return sqrt(pow(m_x - point.m_x, 2) + pow(m_y - point.m_y, 2));
}

template<typename T>
bool CPointBase<T>::operator==(CPointBase<T> point)
{
  return m_x == point.m_x && m_y == point.m_y;
}

template<typename T>
bool CPointBase<T>::operator!=(CPointBase<T> point)
{
  return !(*this == point);
}

template<typename T>
inline bool CPointBase<T>::operator>(CPointBase<T> point)
{
  return
    m_x >= point.m_x && m_y >  point.m_y ||
    m_x >  point.m_x && m_y >= point.m_y;
}

template<typename T>
inline bool CPointBase<T>::operator<(CPointBase<T> point)
{
  return
    m_x <= point.m_x && m_y <  point.m_y ||
    m_x <  point.m_x && m_y <= point.m_y;
}

template<typename T>
inline bool CPointBase<T>::operator>=(CPointBase<T> point)
{
  return *this > point || *this == point;
}

template<typename T>
inline bool CPointBase<T>::operator<=(CPointBase<T> point)
{
  return *this < point || *this == point;
}

template<typename T>
inline CPointBase<T> CPointBase<T>::operator+(CPointBase<T> point)
{
  return CPointBase(m_x + point.m_x, m_y + point.m_y);
}

template<typename T>
inline CPointBase<T> CPointBase<T>::operator-(CPointBase<T> point)
{
  return CPointBase(m_x - point.m_x, m_y - point.m_y);
}

template<typename T>
CPointBase<T> & CPointBase<T>::operator+=(CPointBase<T> point)
{
  m_x += point.m_x;
  m_y += point.m_y;
  return *this;
}

template<typename T>
CPointBase<T> & CPointBase<T>::operator-=(CPointBase<T> point)
{
  m_x -= point.m_x;
  m_y -= point.m_y;
  return *this;
}