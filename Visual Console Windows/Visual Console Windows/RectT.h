//RectT.h
#pragma once
#include <algorithm>
#include "Point.h"
#include "Size.h"
#include "sfinae.h"

#undef max
#undef min

#pragma warning(push)
#pragma warning(disable : 4544)

template<typename T>
class RectT
{
public:
    RectT() = default;
    RectT(PointT<T> position, SizeT<T> size);
    RectT(PointT<T> position, T width, T height);
    RectT(T x, T y, SizeT<T> size);
    RectT(T x, T y, T width, T height);

    void set(PointT<T> position, SizeT<T> size);
    void set(PointT<T> position, T width, T height);
    void set(T x, T y, SizeT<T> size);
    void set(T x, T y, T width, T height);

    T    x() const;
    void x(T x);
    T    y() const;
    void y(T y);
    T    width() const;
    void width(T width);
    T    height() const;
    void height(T height);

    T    left() const;
    void left(T left);
    T    top() const;
    void top(T top);
    T    right() const;
    void right(T right);
    T    bottom() const;
    void bottom(T bottom);

    PointT<T> leftTop() const;
    void         leftTop(PointT<T>);
    void         leftTop(T, T);
    PointT<T> rightTop() const;
    void         rightTop(PointT<T>);
    void         rightTop(T, T);
    PointT<T> leftBottom() const;
    void         leftBottom(PointT<T>);
    void         leftBottom(T, T);
    PointT<T> rightBottom() const;
    void         rightBottom(PointT<T>);
    void         rightBottom(T, T);

    PointT<T> center() const;
    void         center(PointT<T>);
    void         center(T, T);
    PointT<T> position() const;
    void         position(PointT<T>);
    void         position(T, T);
    SizeT<T>  size() const;
    void         size(SizeT<T>);
    void         size(T, T);

    T            square() const;
    void         expand(T left, T top, T right, T bottom);
    PointT<T> localPoint(PointT<T> absolutePoint) const;
    PointT<T> localPoint(T x, T y) const;
    PointT<T> absolutePoint(PointT<T> localPoint) const;
    PointT<T> absolutePoint(T x, T y) const;

    bool isIntersectWith(const RectT& rect) const;
    bool hasRect(const RectT& rect) const;
    bool hasPoint(PointT<T> point) const;
    bool isZero() const;
    bool isEmpty() const;

    RectT  operator+ (const RectT&) const;
    RectT  operator* (const RectT&) const;
    RectT& operator+=(const RectT&);
    RectT& operator*=(const RectT&);
    bool      operator==(const RectT&) const;
    bool      operator!=(const RectT&) const;

    template<typename Func, typename = sfinae::if_function<Func, void, T, T>>
    void      forEach(Func);

private:
    PointT<T> m_position;
    SizeT<T>  m_size;
};

////////////////impementation////////////////

template<typename T>
RectT<T>::RectT(PointT<T> position, SizeT<T> size)
    : m_position(position)
    , m_size(size)
{}

template<typename T>
RectT<T>::RectT(PointT<T> position, T width, T height)
    : m_position(position)
    , m_size(width, height)
{}

template<typename T>
RectT<T>::RectT(T x, T y, SizeT<T> size)
    : m_position(x, y)
    , m_size(size)
{}

template<typename T>
RectT<T>::RectT(T x, T y, T width, T height)
    : m_position(x, y)
    , m_size(width, height)
{}

template<typename T>
void RectT<T>::set(PointT<T> position, SizeT<T> size)
{
    m_position = position;
    m_size = size;
}

template<typename T>
void RectT<T>::set(PointT<T> position, T width, T height)
{
    m_position = position;
    m_size.set(width, height);
}

template<typename T>
void RectT<T>::set(T x, T y, SizeT<T> size)
{
    m_position.set(x, y);
    m_size = size;
}

template<typename T>
void RectT<T>::set(T x, T y, T width, T height)
{
    m_position.set(x, y);
    m_size.set(width, height);
}

template<typename T>
T RectT<T>::x() const
{
    return m_position.x();
}

template<typename T>
void RectT<T>::x(T x)
{
    m_position.x(x);
}

template<typename T>
T RectT<T>::y() const
{
    return m_position.y();
}

template<typename T>
void RectT<T>::y(T y)
{
    m_position.y(y);
}

template<typename T>
T RectT<T>::width() const
{
    return m_size.width();
}

template<typename T>
void RectT<T>::width(T width)
{
    m_size.width(width);
}

template<typename T>
T RectT<T>::height() const
{
    return m_size.height();
}

template<typename T>
void RectT<T>::height(T height)
{
    m_size.height(height);
}

template<typename T>
T RectT<T>::left() const
{
    return m_position.x();
}

template<typename T>
void RectT<T>::left(T left)
{
    T right = this->right();
    left = std::min(right, left);
    m_size.width(right - left);
    m_position.x(left);
}

template<typename T>
T RectT<T>::top() const
{
    return m_position.y();
}

template<typename T>
void RectT<T>::top(T top)
{
    T bottom = this->bottom();
    top = std::min(bottom, top);
    m_size.height(bottom - top);
    m_position.y(top);
}

template<typename T>
T RectT<T>::right() const
{
    return m_position.x() + m_size.width();
}

template<typename T>
void RectT<T>::right(T right)
{
    m_size.width(right - m_position.x());
}

template<typename T>
T RectT<T>::bottom() const
{
    return m_position.y() + m_size.height();
}

template<typename T>
void RectT<T>::bottom(T bottom)
{
    m_size.height(bottom - m_position.y());
}

template<typename T>
inline PointT<T> RectT<T>::leftTop() const
{
    return m_position;
}

template<typename T>
void RectT<T>::leftTop(PointT<T> point)
{
    leftTop(point.x(), point.y());
}

template<typename T>
void RectT<T>::leftTop(T l, T t)
{
    left(l);
    top(t);
}

template<typename T>
PointT<T> RectT<T>::rightTop() const
{
    return PointT<T>(right(), m_position.y());
}

template<typename T>
void RectT<T>::rightTop(PointT<T> point)
{
    rightTop(point.x(), point.y());
}

template<typename T>
void RectT<T>::rightTop(T r, T t)
{
    right(r);
    top(t);
}

template<typename T>
PointT<T> RectT<T>::leftBottom() const
{
    return PointT<T>(m_position.x(), bottom());
}

template<typename T>
void RectT<T>::leftBottom(PointT<T> point)
{
    leftBottom(point.x(), point.y());
}

template<typename T>
void RectT<T>::leftBottom(T l, T b)
{
    left(l);
    bottom(b);
}

template<typename T>
PointT<T> RectT<T>::rightBottom() const
{
    return PointT<T>(right(), bottom());
}

template<typename T>
void RectT<T>::rightBottom(PointT<T> point)
{
    rightBottom(point.x(), point.y());
}

template<typename T>
void RectT<T>::rightBottom(T r, T b)
{
    right(r);
    bottom(b);
}

template<typename T>
PointT<T> RectT<T>::center() const
{
    return PointT<T>(m_position.x() + m_size.width() / 2, m_position.y() + m_size.height() / 2);
}

template<typename T>
void RectT<T>::center(PointT<T> point)
{
    m_position += point - center();
}

template<typename T>
void RectT<T>::center(T x, T y)
{
    center(PointT<T>(x, y));
}

template<typename T>
inline PointT<T> RectT<T>::position() const
{
    return m_position;
}

template<typename T>
void RectT<T>::position(PointT<T> position)
{
    m_position = position;
}

template<typename T>
void RectT<T>::position(T x, T y)
{
    m_position.set(x, y);
}

template<typename T>
inline SizeT<T> RectT<T>::size() const
{
    return m_size;
}

template<typename T>
void RectT<T>::size(SizeT<T> size)
{
    m_size = size;
}

template<typename T>
void RectT<T>::size(T width, T height)
{
    m_size.set(width, height);
}

template<typename T>
T RectT<T>::square() const
{
    return m_size.square();
}

template<typename T>
void RectT<T>::expand(T left, T top, T right, T bottom)
{
    m_position.shift(-left, -top);
    m_size.inc(left + right, top + bottom);
}

template<typename T>
PointT<T> RectT<T>::localPoint(PointT<T> absolutePoint) const
{
    return absolutePoint - m_position;
}

template<typename T>
PointT<T> RectT<T>::localPoint(T x, T y) const
{
    return PointT<T>(x, y) - m_position;
}

template<typename T>
PointT<T> RectT<T>::absolutePoint(PointT<T> localPoint) const
{
    return localPoint + m_position;
}

template<typename T>
PointT<T> RectT<T>::absolutePoint(T x, T y) const
{
    return PointT<T>(x, y) + m_position;
}

template<typename T>
bool RectT<T>::isIntersectWith(const RectT& rect) const
{
    return rightBottom() > rect.m_position && rect.rightBottom() > m_position;
}

template<typename T>
bool RectT<T>::hasRect(const RectT& rect) const
{
    return rect.m_position >= m_position && rect.rightBottom() <= rightBottom();
}

template<typename T>
bool RectT<T>::hasPoint(PointT<T> point) const
{
    return point >= m_position && point <= (rightBottom() - PointT<T>(1, 1));
}

template<typename T>
bool RectT<T>::isZero() const
{
    return m_size.isZero() && m_position.isZero();
}

template<typename T>
bool RectT<T>::isEmpty() const
{
    return m_size.isEmpty();
}

template<typename T>
RectT<T> RectT<T>::operator+(const RectT& rect) const
{
    return RectT(*this) += rect;
}

template<typename T>
RectT<T> RectT<T>::operator*(const RectT& rect) const
{
    return RectT(*this) *= rect;
}

template<typename T>
RectT<T>& RectT<T>::operator+=(const RectT& rect)
{
    left(std::min(left(), rect.left()));
    top(std::min(top(), rect.top()));
    right(std::max(right(), rect.right()));
    bottom(std::max(bottom(), rect.bottom()));
    return *this;
}

template<typename T>
RectT<T>& RectT<T>::operator*=(const RectT& rect)
{
    auto l1 = left();
    auto l2 = rect.left();
    auto l3 = std::min(left(), rect.left());
    auto t1 = top();
    auto t2 = rect.top();
    auto t3 = std::min(top(), rect.top());
    auto r1 = right();
    auto r2 = rect.right();
    auto r3 = std::max(right(), rect.right());
    left(std::max(left(), rect.left()));
    top(std::max(top(), rect.top()));
    right(std::min(right(), rect.right()));
    bottom(std::min(bottom(), rect.bottom()));
    return *this;
}

template<typename T>
bool RectT<T>::operator==(const RectT& rect) const
{
    return m_position == rect.m_position && m_size == rect.m_size;
}

template<typename T>
bool RectT<T>::operator!=(const RectT& rect) const
{
    return !operator==(rect);
}

template<typename T>
template<typename Func, typename = sfinae::if_function<Func, void, T, T>>
void RectT<T>::forEach(Func func)
{
    auto bottom = this->bottom();
    auto right = this->right();
    auto left = this->left();
    for(auto i = top(); i < bottom; ++i)
    {
        for(auto j = left; j < right; ++j)
        {
            func(i, j);
        }
    }
}

#pragma warning(pop)
