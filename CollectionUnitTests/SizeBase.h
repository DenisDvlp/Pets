#pragma once
#include "RectBase.h"

template<typename T>
class CRectBase;

template<typename T>
class CSizeBase
{
  T m_width  = 0;
  T m_height = 0;

public:

  CSizeBase();
  CSizeBase(T width, T height);

  void         set(T width, T height);

  T            width();
  void         width(T width);
  T            height();
  void         height(T height);

  CRectBase<T> rect();

  bool         isZero();
  bool         isEmpty();
  T            square();
  void         inc(T dwidth, T dheight);

  bool         operator==(CSizeBase &size);
  bool         operator!=(CSizeBase &size);
};

////////////////impementation////////////////

template<typename T>
CSizeBase<T>::CSizeBase() {}

template<typename T>
CSizeBase<T>::CSizeBase(T width, T height)
{
  this->width(width);
  this->height(height);
}

template<typename T>
void CSizeBase<T>::set(T width, T height)
{
  this->width(width);
  this->height(height);
}

template<typename T>
inline T CSizeBase<T>::width()
{
  return m_width;
}

template<typename T>
inline void CSizeBase<T>::width(T width)
{
  m_width = width < 0 ? 0 : width;
}

template<typename T>
inline T CSizeBase<T>::height()
{
  return m_height;
}

template<typename T>
inline void CSizeBase<T>::height(T height)
{
  m_height = height < 0 ? 0 : height;
}

template<typename T>
inline CRectBase<T> CSizeBase<T>::rect()
{
  return CRectBase<T>(0, 0, m_width, m_height);
}

template<typename T>
bool CSizeBase<T>::isZero()
{
  return !(m_width | m_height);
}

template<typename T>
bool CSizeBase<T>::isEmpty()
{
  return !m_width || !m_height;
}

template<typename T>
inline T CSizeBase<T>::square()
{
  return m_width * m_height;
}

template<typename T>
void CSizeBase<T>::inc(T dwidth, T dheight)
{
  width(m_width + dwidth);
  height(m_height + dheight);
}

template<typename T>
bool CSizeBase<T>::operator==(CSizeBase<T> &size)
{
  return m_width == size.m_width && m_height == size.m_height;
}

template<typename T>
bool CSizeBase<T>::operator!=(CSizeBase<T> &size)
{
  return !(*this == size);
}