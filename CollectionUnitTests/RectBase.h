#pragma once
#include "PointBase.h"
#include "SizeBase.h"
#include "Utils.h"

template<typename T>
class CSizeBase;

template<typename T>
class CPointBase;

template<typename T>
class CRectBase
{
  CPointBase<T> m_position;
  CSizeBase<T>  m_size;

public:

  CRectBase<T>();
  CRectBase<T>(CPointBase<T> position, CSizeBase<T> size);
  CRectBase<T>(CPointBase<T> position, T width, T height);
  CRectBase<T>(T x, T y, CSizeBase<T> size);
  CRectBase<T>(T x, T y, T width, T height);

  void          set(CPointBase<T> position, CSizeBase<T> size);
  void          set(CPointBase<T> position, T width, T height);
  void          set(T x, T y, CSizeBase<T> size);
  void          set(T x, T y, T width, T height);

  T             x();
  void          x(T x);
  T             y();
  void          y(T y);
  T             width();
  void          width(T width);
  T             height();
  void          height(T height);

  T             left();
  void          left(T left);
  T             top();
  void          top(T top);
  T             right();
  void          right(T right);
  T             bottom();
  void          bottom(T bottom);

  CPointBase<T> leftTop();
  void          leftTop(CPointBase<T> point);
  void          leftTop(T left, T top);
  CPointBase<T> rightTop();
  void          rightTop(CPointBase<T> point);
  void          rightTop(T right, T top);
  CPointBase<T> leftBottom();
  void          leftBottom(CPointBase<T> point);
  void          leftBottom(T left, T bottom);
  CPointBase<T> rightBottom();
  void          rightBottom(CPointBase<T> point);
  void          rightBottom(T right, T bottom);

  CPointBase<T> center();
  void          center(CPointBase<T> center);
  void          center(T x, T y);
  CPointBase<T> position();
  void          position(CPointBase<T> position);
  void          position(T x, T y);
  CSizeBase<T>  size();
  void          size(CSizeBase<T> size);
  void          size(T width, T height);

  T             square();
  void          expand(T left, T top, T right, T bottom);
  CPointBase<T> localPoint(CPointBase<T> absolutePoint);
  CPointBase<T> localPoint(T x, T y);
  CPointBase<T> absolutePoint(CPointBase<T> localPoint);
  CPointBase<T> absolutePoint(T x, T y);

  bool          isIntersectWith(CRectBase<T> rect);
  bool          hasRect(CRectBase<T> rect);
  bool          hasPoint(CPointBase<T> point);
  bool          isZero();
  bool          isEmpty();

  CRectBase<T>  operator+(CRectBase<T> rect);
  CRectBase<T>  operator*(CRectBase<T> rect);
  CRectBase<T>& operator+=(CRectBase<T> rect);
  CRectBase<T>& operator*=(CRectBase<T> rect);
  bool          operator==(CRectBase<T> rect);
  bool          operator!=(CRectBase<T> rect);
};

////////////////impementation////////////////

template<typename T>
CRectBase<T>::CRectBase() {}

template<typename T>
CRectBase<T>::CRectBase(CPointBase<T> position, CSizeBase<T> size) :
  m_position(position),
  m_size(size)
{}

template<typename T>
CRectBase<T>::CRectBase(CPointBase<T> position, T width, T height) :
  m_position(position),
  m_size(width, height)
{}

template<typename T>
CRectBase<T>::CRectBase(T x, T y, CSizeBase<T> size) :
  m_position(x, y),
  m_size(size)
{}

template<typename T>
CRectBase<T>::CRectBase(T x, T y, T width, T height) :
  m_position(x, y),
  m_size(width, height)
{}

template<typename T>
void CRectBase<T>::set(CPointBase<T> position, CSizeBase<T> size)
{
  m_position = position;
  m_size = size;
}

template<typename T>
void CRectBase<T>::set(CPointBase<T> position, T width, T height)
{
  m_position = position;
  m_size.set(width, height);
}

template<typename T>
void CRectBase<T>::set(T x, T y, CSizeBase<T> size)
{
  m_position.set(x, y);
  m_size = size;
}

template<typename T>
void CRectBase<T>::set(T x, T y, T width, T height)
{
  m_position.set(x, y);
  m_size.set(width, height);
}

template<typename T>
T CRectBase<T>::x()
{
  return m_position.x();
}

template<typename T>
void CRectBase<T>::x(T x)
{
  m_position.x(x);
}

template<typename T>
T CRectBase<T>::y()
{
  return m_position.y();
}

template<typename T>
void CRectBase<T>::y(T y)
{
  m_position.y(y);
}

template<typename T>
T CRectBase<T>::width()
{
  return m_size.width();
}

template<typename T>
void CRectBase<T>::width(T width)
{
  m_size.width(width);
}

template<typename T>
T CRectBase<T>::height()
{
  return m_size.height();
}

template<typename T>
void CRectBase<T>::height(T height)
{
  m_size.height(height);
}

template<typename T>
T CRectBase<T>::left()
{
  return m_position.x();
}

template<typename T>
inline void CRectBase<T>::left(T left)
{
  T right = this->right();
  left = min(right, left);
  m_size.width(right - left);
  m_position.x(left);
}

template<typename T>
T CRectBase<T>::top()
{
  return m_position.y();
}

template<typename T>
inline void CRectBase<T>::top(T top)
{
  T bottom = this->bottom();
  top = min(bottom, top);
  m_size.height(bottom - top);
  m_position.y(top);
}

template<typename T>
inline T CRectBase<T>::right()
{
  return m_position.x() + m_size.width();
}

template<typename T>
inline void CRectBase<T>::right(T right)
{
  m_size.width(right - m_position.x());
}

template<typename T>
inline T CRectBase<T>::bottom()
{
  return m_position.y() + m_size.height();
}

template<typename T>
inline void CRectBase<T>::bottom(T bottom)
{
  m_size.height(bottom - m_position.y());
}

template<typename T>
inline CPointBase<T> CRectBase<T>::leftTop()
{
  return m_position;
}

template<typename T>
inline void CRectBase<T>::leftTop(CPointBase<T> point)
{
  left(point.x());
  top(point.y());
}

template<typename T>
void CRectBase<T>::leftTop(T left, T top)
{
  this->left(left);
  this->top(top);
}

template<typename T>
inline CPointBase<T> CRectBase<T>::rightTop()
{
  return CPointBase<T>(right(), m_position.y());
}

template<typename T>
inline void CRectBase<T>::rightTop(CPointBase<T> point)
{
  right(point.x());
  top(point.y());
}

template<typename T>
void CRectBase<T>::rightTop(T right, T top)
{
  this->right(right);
  this->top(top);
}

template<typename T>
inline CPointBase<T> CRectBase<T>::leftBottom()
{
  return CPointBase<T>(m_position.x(), bottom());
}

template<typename T>
inline void CRectBase<T>::leftBottom(CPointBase<T> point)
{
  left(point.x());
  bottom(point.y());
}

template<typename T>
void CRectBase<T>::leftBottom(T left, T bottom)
{
  this->left(left);
  this->bottom(bottom);
}

template<typename T>
inline CPointBase<T> CRectBase<T>::rightBottom()
{
  return CPointBase<T>(right(), bottom());
}

template<typename T>
inline void CRectBase<T>::rightBottom(CPointBase<T> point)
{
  right(point.x());
  bottom(point.y());
}

template<typename T>
void CRectBase<T>::rightBottom(T right, T bottom)
{
  this->right(right);
  this->bottom(bottom);
}

template<typename T>
inline CPointBase<T> CRectBase<T>::center()
{
  return CPointBase<T>(m_position.x() + m_size.width() / 2, m_position.y() + m_size.height() / 2);
}

template<typename T>
inline void CRectBase<T>::center(CPointBase<T> point)
{
  m_position += point - center();
}

template<typename T>
void CRectBase<T>::center(T x, T y)
{
  center(CPointBase<T>(x, y));
}

template<typename T>
CPointBase<T> CRectBase<T>::position()
{
  return m_position;
}

template<typename T>
void CRectBase<T>::position(CPointBase<T> position)
{
  m_position = position;
}

template<typename T>
void CRectBase<T>::position(T x, T y)
{
  m_position.set(x, y);
}

template<typename T>
CSizeBase<T> CRectBase<T>::size()
{
  return m_size;
}

template<typename T>
void CRectBase<T>::size(CSizeBase<T> size)
{
  m_size = size;
}

template<typename T>
void CRectBase<T>::size(T width, T height)
{
  m_size.set(width, height);
}

template<typename T>
T CRectBase<T>::square()
{
  return m_size.square();
}

template<typename T>
void CRectBase<T>::expand(T left, T top, T right, T bottom)
{
  m_position.shift(-left, -top);
  m_size.inc(right + left, top + bottom);
}

template<typename T>
CPointBase<T> CRectBase<T>::localPoint(CPointBase<T> absolutePoint)
{
  return absolutePoint - m_position;
}

template<typename T>
CPointBase<T> CRectBase<T>::localPoint(T x, T y)
{
  return CPointBase<T>(x, y) - m_position;
}

template<typename T>
CPointBase<T> CRectBase<T>::absolutePoint(CPointBase<T> localPoint)
{
  return localPoint + m_position;
}

template<typename T>
CPointBase<T> CRectBase<T>::absolutePoint(T x, T y)
{
  return CPointBase<T>(x, y) + m_position;
}

template<typename T>
bool CRectBase<T>::isIntersectWith(CRectBase<T> rect)
{
  return
    rightBottom() > rect.m_position &&
    rect.rightBottom() > m_position;
}

template<typename T>
bool CRectBase<T>::hasRect(CRectBase<T> rect)
{
  return rect.m_position >= m_position && rect.rightBottom() <= rightBottom();
}

template<typename T>
bool CRectBase<T>::hasPoint(CPointBase<T> point)
{
  return point >= m_position && point < rightBottom();
}

template<typename T>
bool CRectBase<T>::isZero()
{
  return m_size.isZero() && m_position.isZero();
}

template<typename T>
bool CRectBase<T>::isEmpty()
{
  return m_size.isEmpty();
}

template<typename T>
CRectBase<T> CRectBase<T>::operator+(CRectBase<T> rect)
{
  CRectBase<T> r(utils::min(m_position, rect.m_position), 0, 0);
  r.rightBottom(utils::max(rightBottom(), rect.rightBottom()));
  return r;
}

template<typename T>
CRectBase<T> CRectBase<T>::operator*(CRectBase<T> rect)
{
  CRectBase<T> r(utils::max(m_position, rect.m_position), 0, 0);
  r.rightBottom(utils::min(rightBottom(), rect.rightBottom()));
  return r;
}

template<typename T>
CRectBase<T> & CRectBase<T>::operator+=(CRectBase<T> rect)
{
  m_position = utils::min(m_position, rect.m_position);
  rightBottom(utils::max(rightBottom(), rect.rightBottom()));
  return *this;
}

template<typename T>
CRectBase<T> & CRectBase<T>::operator*=(CRectBase<T> rect)
{
  m_position = utils::max(m_position, rect.m_position);
  rightBottom(utils::min(rightBottom(), rect.rightBottom()));
  return *this;
}

template<typename T>
bool CRectBase<T>::operator==(CRectBase<T> rect)
{
  return m_position == rect.m_position && m_size == rect.m_size;
}

template<typename T>
bool CRectBase<T>::operator!=(CRectBase<T> rect)
{
  return !(*this == rect);
}