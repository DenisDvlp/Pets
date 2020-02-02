//PointBase.h
#pragma once
#include <cmath>

template<typename T>
class PointT
{
public:
  PointT() = default;
  PointT(T, T);

  void set(T, T);
  void shift(T, T);
  void shift(const PointT&);

  T    x() const;
  void x(T);
  T    y() const;
  void y(T);

  bool isZero() const;
  double distance(const PointT&) const;

  bool operator==(const PointT&) const;
  bool operator!=(const PointT&) const;
  bool operator> (const PointT&) const;
  bool operator< (const PointT&) const;
  bool operator>=(const PointT&) const;
  bool operator<=(const PointT&) const;
  PointT operator+ (const PointT&) const;
  PointT operator- (const PointT&) const;
  PointT operator- () const;
  PointT& operator+=(const PointT&);
  PointT& operator-=(const PointT&);

private:
  T m_x = 0;
  T m_y = 0;
};

////////////////impementation////////////////

template<typename T>
PointT<T>::PointT(T x, T y) :
  m_x(x),
  m_y(y)
{}

template<typename T>
void PointT<T>::set(T x, T y)
{
  m_x = x;
  m_y = y;
}

template<typename T>
void PointT<T>::shift(T x, T y)
{
  m_x += x;
  m_y += y;
}

template<typename T>
void PointT<T>::shift(const PointT& point)
{
  shift(point.m_x, point.m_y);
}

template<typename T>
inline T PointT<T>::x() const
{
  return m_x;
}

template<typename T>
inline void PointT<T>::x(T x)
{
  m_x = x;
}

template<typename T>
inline T PointT<T>::y() const
{
  return m_y;
}

template<typename T>
inline void PointT<T>::y(T y)
{
  m_y = y;
}

template<typename T>
bool PointT<T>::isZero() const
{
  return !(m_x | m_y);
}

template<typename T>
double PointT<T>::distance(const PointT& point) const
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
bool PointT<T>::operator==(const PointT& point) const
{
  return m_x == point.m_x && m_y == point.m_y;
}

template<typename T>
bool PointT<T>::operator!=(const PointT& point) const
{
  return !operator==(point);
}

template<typename T>
bool PointT<T>::operator>(const PointT& point) const
{
  return
    m_x >= point.m_x && m_y >  point.m_y ||
    m_x >  point.m_x && m_y >= point.m_y;
}

template<typename T>
bool PointT<T>::operator<(const PointT& point) const
{
  return
    m_x <= point.m_x && m_y <  point.m_y ||
    m_x <  point.m_x && m_y <= point.m_y;
}

template<typename T>
bool PointT<T>::operator>=(const PointT& point) const
{
  return operator>(point) || operator==(point);
}

template<typename T>
bool PointT<T>::operator<=(const PointT& point) const
{
  return operator<(point) || operator==(point);
}

template<typename T>
PointT<T> PointT<T>::operator+(const PointT& point) const
{
  return PointT(m_x + point.m_x, m_y + point.m_y);
}

template<typename T>
PointT<T> PointT<T>::operator-(const PointT& point) const
{
  return PointT(m_x - point.m_x, m_y - point.m_y);
}

template<typename T>
PointT<T> PointT<T>::operator-() const
{
  return PointT(-m_x, -m_y);
}

template<typename T>
PointT<T>& PointT<T>::operator+=(const PointT& point)
{
  shift(point);
  return *this;
}

template<typename T>
PointT<T>& PointT<T>::operator-=(const PointT& point)
{
  shift(-point);
  return *this;
}