#pragma once
#include "PointBase.h"
#include "SizeBase.h"
#include "Utils.h"

template<typename T>
class SizeBase;

template<typename T>
class PointBase;

template<typename T>
class RectBase
{
  PointBase<T> m_position;
  SizeBase<T>  m_size;

public:

  RectBase<T>();
  RectBase<T>(PointBase<T> position, SizeBase<T> size);
  RectBase<T>(PointBase<T> position, T width, T height);
  RectBase<T>(T x, T y, SizeBase<T> size);
  RectBase<T>(T x, T y, T width, T height);

  void          set(PointBase<T> position, SizeBase<T> size);
  void          set(PointBase<T> position, T width, T height);
  void          set(T x, T y, SizeBase<T> size);
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

  PointBase<T>  leftTop();
  void          leftTop(PointBase<T> point);
  void          leftTop(T left, T top);
  PointBase<T>  rightTop();
  void          rightTop(PointBase<T> point);
  void          rightTop(T right, T top);
  PointBase<T>  leftBottom();
  void          leftBottom(PointBase<T> point);
  void          leftBottom(T left, T bottom);
  PointBase<T>  rightBottom();
  void          rightBottom(PointBase<T> point);
  void          rightBottom(T right, T bottom);

  PointBase<T>  center();
  void          center(PointBase<T> center);
  void          center(T x, T y);
  PointBase<T>  position();
  void          position(PointBase<T> position);
  void          position(T x, T y);
  SizeBase<T>   size();
  void          size(SizeBase<T> size);
  void          size(T width, T height);

  T             square();
  void          expand(T left, T top, T right, T bottom);
  PointBase<T>  localPoint(PointBase<T> absolutePoint);
  PointBase<T>  localPoint(T x, T y);
  PointBase<T>  absolutePoint(PointBase<T> localPoint);
  PointBase<T>  absolutePoint(T x, T y);

  bool          isIntersectWith(RectBase<T> rect);
  bool          hasRect(RectBase<T> rect);
  bool          hasPoint(PointBase<T> point);
  bool          isZero();
  bool          isEmpty();

  RectBase<T>   operator+(RectBase<T> rect);
  RectBase<T>   operator*(RectBase<T> rect);
  RectBase<T>&  operator+=(RectBase<T> rect);
  RectBase<T>&  operator*=(RectBase<T> rect);
  bool          operator==(RectBase<T> rect);
  bool          operator!=(RectBase<T> rect);
};

////////////////impementation////////////////

template<typename T>
RectBase<T>::RectBase() {}

template<typename T>
RectBase<T>::RectBase(PointBase<T> position, SizeBase<T> size) :
  m_position(position),
  m_size(size)
{}

template<typename T>
RectBase<T>::RectBase(PointBase<T> position, T width, T height) :
  m_position(position),
  m_size(width, height)
{}

template<typename T>
RectBase<T>::RectBase(T x, T y, SizeBase<T> size) :
  m_position(x, y),
  m_size(size)
{}

template<typename T>
RectBase<T>::RectBase(T x, T y, T width, T height) :
  m_position(x, y),
  m_size(width, height)
{}

template<typename T>
void RectBase<T>::set(PointBase<T> position, SizeBase<T> size)
{
  m_position = position;
  m_size = size;
}

template<typename T>
void RectBase<T>::set(PointBase<T> position, T width, T height)
{
  m_position = position;
  m_size.set(width, height);
}

template<typename T>
void RectBase<T>::set(T x, T y, SizeBase<T> size)
{
  m_position.set(x, y);
  m_size = size;
}

template<typename T>
void RectBase<T>::set(T x, T y, T width, T height)
{
  m_position.set(x, y);
  m_size.set(width, height);
}

template<typename T>
T RectBase<T>::x()
{
  return m_position.x();
}

template<typename T>
void RectBase<T>::x(T x)
{
  m_position.x(x);
}

template<typename T>
T RectBase<T>::y()
{
  return m_position.y();
}

template<typename T>
void RectBase<T>::y(T y)
{
  m_position.y(y);
}

template<typename T>
T RectBase<T>::width()
{
  return m_size.width();
}

template<typename T>
void RectBase<T>::width(T width)
{
  m_size.width(width);
}

template<typename T>
T RectBase<T>::height()
{
  return m_size.height();
}

template<typename T>
void RectBase<T>::height(T height)
{
  m_size.height(height);
}

template<typename T>
T RectBase<T>::left()
{
  return m_position.x();
}

template<typename T>
inline void RectBase<T>::left(T left)
{
  T right = this->right();
  left = min(right, left);
  m_size.width(right - left);
  m_position.x(left);
}

template<typename T>
T RectBase<T>::top()
{
  return m_position.y();
}

template<typename T>
inline void RectBase<T>::top(T top)
{
  T bottom = this->bottom();
  top = min(bottom, top);
  m_size.height(bottom - top);
  m_position.y(top);
}

template<typename T>
inline T RectBase<T>::right()
{
  return m_position.x() + m_size.width();
}

template<typename T>
inline void RectBase<T>::right(T right)
{
  m_size.width(right - m_position.x());
}

template<typename T>
inline T RectBase<T>::bottom()
{
  return m_position.y() + m_size.height();
}

template<typename T>
inline void RectBase<T>::bottom(T bottom)
{
  m_size.height(bottom - m_position.y());
}

template<typename T>
inline PointBase<T> RectBase<T>::leftTop()
{
  return m_position;
}

template<typename T>
inline void RectBase<T>::leftTop(PointBase<T> point)
{
  left(point.x());
  top(point.y());
}

template<typename T>
void RectBase<T>::leftTop(T left, T top)
{
  this->left(left);
  this->top(top);
}

template<typename T>
inline PointBase<T> RectBase<T>::rightTop()
{
  return PointBase<T>(right(), m_position.y());
}

template<typename T>
inline void RectBase<T>::rightTop(PointBase<T> point)
{
  right(point.x());
  top(point.y());
}

template<typename T>
void RectBase<T>::rightTop(T right, T top)
{
  this->right(right);
  this->top(top);
}

template<typename T>
inline PointBase<T> RectBase<T>::leftBottom()
{
  return PointBase<T>(m_position.x(), bottom());
}

template<typename T>
inline void RectBase<T>::leftBottom(PointBase<T> point)
{
  left(point.x());
  bottom(point.y());
}

template<typename T>
void RectBase<T>::leftBottom(T left, T bottom)
{
  this->left(left);
  this->bottom(bottom);
}

template<typename T>
inline PointBase<T> RectBase<T>::rightBottom()
{
  return PointBase<T>(right(), bottom());
}

template<typename T>
inline void RectBase<T>::rightBottom(PointBase<T> point)
{
  right(point.x());
  bottom(point.y());
}

template<typename T>
void RectBase<T>::rightBottom(T right, T bottom)
{
  this->right(right);
  this->bottom(bottom);
}

template<typename T>
inline PointBase<T> RectBase<T>::center()
{
  return PointBase<T>(m_position.x() + m_size.width() / 2, m_position.y() + m_size.height() / 2);
}

template<typename T>
inline void RectBase<T>::center(PointBase<T> point)
{
  m_position += point - center();
}

template<typename T>
void RectBase<T>::center(T x, T y)
{
  center(PointBase<T>(x, y));
}

template<typename T>
PointBase<T> RectBase<T>::position()
{
  return m_position;
}

template<typename T>
void RectBase<T>::position(PointBase<T> position)
{
  m_position = position;
}

template<typename T>
void RectBase<T>::position(T x, T y)
{
  m_position.set(x, y);
}

template<typename T>
SizeBase<T> RectBase<T>::size()
{
  return m_size;
}

template<typename T>
void RectBase<T>::size(SizeBase<T> size)
{
  m_size = size;
}

template<typename T>
void RectBase<T>::size(T width, T height)
{
  m_size.set(width, height);
}

template<typename T>
T RectBase<T>::square()
{
  return m_size.square();
}

template<typename T>
void RectBase<T>::expand(T left, T top, T right, T bottom)
{
  m_position.shift(-left, -top);
  m_size.inc(right + left, top + bottom);
}

template<typename T>
PointBase<T> RectBase<T>::localPoint(PointBase<T> absolutePoint)
{
  return absolutePoint - m_position;
}

template<typename T>
PointBase<T> RectBase<T>::localPoint(T x, T y)
{
  return PointBase<T>(x, y) - m_position;
}

template<typename T>
PointBase<T> RectBase<T>::absolutePoint(PointBase<T> localPoint)
{
  return localPoint + m_position;
}

template<typename T>
PointBase<T> RectBase<T>::absolutePoint(T x, T y)
{
  return PointBase<T>(x, y) + m_position;
}

template<typename T>
bool RectBase<T>::isIntersectWith(RectBase<T> rect)
{
  return
    rightBottom() > rect.m_position &&
    rect.rightBottom() > m_position;
}

template<typename T>
bool RectBase<T>::hasRect(RectBase<T> rect)
{
  return rect.m_position >= m_position && rect.rightBottom() <= rightBottom();
}

template<typename T>
bool RectBase<T>::hasPoint(PointBase<T> point)
{
  return point >= m_position && point < rightBottom();
}

template<typename T>
bool RectBase<T>::isZero()
{
  return m_size.isZero() && m_position.isZero();
}

template<typename T>
bool RectBase<T>::isEmpty()
{
  return m_size.isEmpty();
}

template<typename T>
RectBase<T> RectBase<T>::operator+(RectBase<T> rect)
{
  RectBase<T> r(utils::min(m_position, rect.m_position), 0, 0);
  r.rightBottom(utils::max(rightBottom(), rect.rightBottom()));
  return r;
}

template<typename T>
RectBase<T> RectBase<T>::operator*(RectBase<T> rect)
{
  RectBase<T> r(utils::max(m_position, rect.m_position), 0, 0);
  r.rightBottom(utils::min(rightBottom(), rect.rightBottom()));
  return r;
}

template<typename T>
RectBase<T> & RectBase<T>::operator+=(RectBase<T> rect)
{
  m_position = utils::min(m_position, rect.m_position);
  rightBottom(utils::max(rightBottom(), rect.rightBottom()));
  return *this;
}

template<typename T>
RectBase<T> & RectBase<T>::operator*=(RectBase<T> rect)
{
  m_position = utils::max(m_position, rect.m_position);
  rightBottom(utils::min(rightBottom(), rect.rightBottom()));
  return *this;
}

template<typename T>
bool RectBase<T>::operator==(RectBase<T> rect)
{
  return m_position == rect.m_position && m_size == rect.m_size;
}

template<typename T>
bool RectBase<T>::operator!=(RectBase<T> rect)
{
  return !(*this == rect);
}