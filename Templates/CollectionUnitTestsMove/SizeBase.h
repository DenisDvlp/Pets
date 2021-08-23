//SizeBase.h
#pragma once
#include "RectBase.h"

template<typename T>
class RectBase;

template<typename T>
class SizeBase
{
  T m_width  = 0;
  T m_height = 0;

public:

  SizeBase();
  SizeBase(T width, T height);

  void         set(T width, T height);

  T            width();
  void         width(T width);
  T            height();
  void         height(T height);

  RectBase<T> rect();

  bool         isZero();
  bool         isEmpty();
  T            square();
  void         inc(T dwidth, T dheight);

  bool         operator==(SizeBase &size);
  bool         operator!=(SizeBase &size);
};

////////////////impementation////////////////

template<typename T>
SizeBase<T>::SizeBase() {}

template<typename T>
SizeBase<T>::SizeBase(T width, T height)
{
  this->width(width);
  this->height(height);
}

template<typename T>
void SizeBase<T>::set(T width, T height)
{
  this->width(width);
  this->height(height);
}

template<typename T>
inline T SizeBase<T>::width()
{
  return m_width;
}

template<typename T>
inline void SizeBase<T>::width(T width)
{
  m_width = width < 0 ? 0 : width;
}

template<typename T>
inline T SizeBase<T>::height()
{
  return m_height;
}

template<typename T>
inline void SizeBase<T>::height(T height)
{
  m_height = height < 0 ? 0 : height;
}

template<typename T>
inline RectBase<T> SizeBase<T>::rect()
{
  return RectBase<T>(0, 0, m_width, m_height);
}

template<typename T>
bool SizeBase<T>::isZero()
{
  return !(m_width | m_height);
}

template<typename T>
bool SizeBase<T>::isEmpty()
{
  return !m_width || !m_height;
}

template<typename T>
inline T SizeBase<T>::square()
{
  return m_width * m_height;
}

template<typename T>
void SizeBase<T>::inc(T dwidth, T dheight)
{
  width(m_width + dwidth);
  height(m_height + dheight);
}

template<typename T>
bool SizeBase<T>::operator==(SizeBase<T> &size)
{
  return m_width == size.m_width && m_height == size.m_height;
}

template<typename T>
bool SizeBase<T>::operator!=(SizeBase<T> &size)
{
  return !(*this == size);
}