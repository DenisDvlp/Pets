//DRectT.h
#pragma once
#include <algorithm>
#include "DPointT.h"
#include "DSizeT.h"
#include "DSfinae.h"

#undef max
#undef min

template<typename T>
class DRectT
{
public:
    DRectT() = default;
    DRectT(const DSizeT<T>& size);
    DRectT(const DPointT<T>& position, const DSizeT<T>& size);
    DRectT(const DPointT<T>& position, const T width, const T height);
    DRectT(const T x, const T y, const DSizeT<T>& size);
    DRectT(const T x, const T y, const T width, const T height);

    void set(const DPointT<T>& position, const DSizeT<T>& size);
    void set(const DPointT<T>& position, const T width, const T height);
    void set(const T x, const T y, const DSizeT<T>& size);
    void set(const T x, const T y, const T width, const T height);

    T    x() const;
    void x(const T x);
    T    y() const;
    void y(const T y);
    T    width() const;
    void width(const T width);
    T    height() const;
    void height(const T height);

    T    left() const;
    void left(const T left);
    T    top() const;
    void top(const T top);
    T    right() const;
    void right(const T right);
    T    bottom() const;
    void bottom(const T bottom);

    DPointT<T> leftTop() const;
    void       leftTop(const DPointT<T>&);
    void       leftTop(const T, const T);
    DPointT<T> rightTop() const;
    void       rightTop(const DPointT<T>&);
    void       rightTop(const T, const T);
    DPointT<T> leftBottom() const;
    void       leftBottom(const DPointT<T>&);
    void       leftBottom(const T, const T);
    DPointT<T> rightBottom() const;
    void       rightBottom(const DPointT<T>&);
    void       rightBottom(const T, const T);

    DPointT<T> center() const;
    void       center(const DPointT<T>&);
    void       center(const T, const T);
    const DPointT<T>& position() const;
    void       position(const DPointT<T>&);
    void       position(const T, const T);
    const DSizeT<T>& size() const;
    void       size(const DSizeT<T>&);
    void       size(const T, const T);

    T          square() const;
    DPointT<T> localPoint(const DPointT<T>& absolutePoint) const;
    DPointT<T> localPoint(const T x, const T y) const;
    DPointT<T> absolutePoint(const DPointT<T>& localPoint) const;
    DPointT<T> absolutePoint(const T x, const T y) const;

    bool isIntersectedWith(const DRectT& rect) const;
    bool contains(const DRectT& rect) const;
    bool contains(const DPointT<T>& point) const;
    bool isZero() const;
    bool isEmpty() const;

    DRectT  operator* (const double);
    DRectT& operator*=(const double);
    DRectT  operator/ (const double);
    DRectT& operator/=(const double);
    DRectT  operator| (const DRectT&) const;
    DRectT  operator& (const DRectT&) const;
    DRectT& operator|=(const DRectT&);
    DRectT& operator&=(const DRectT&);
    bool    operator==(const DRectT&) const;
    bool    operator!=(const DRectT&) const;

    template<typename Func>
    void forEach(Func) const;

private:
    DPointT<T> m_position;
    DSizeT<T>  m_size;
};

////////////////impementation////////////////


template<typename T>
inline DRectT<T>::DRectT(const DSizeT<T>& size)
    : m_position()
    , m_size(size)
{}

template<typename T>
DRectT<T>::DRectT(const DPointT<T>& position, const DSizeT<T>& size)
    : m_position(position)
    , m_size(size)
{}

template<typename T>
DRectT<T>::DRectT(const DPointT<T>& position, const T width, const T height)
    : m_position(position)
    , m_size(width, height)
{}

template<typename T>
DRectT<T>::DRectT(const T x, const T y, const DSizeT<T>& size)
    : m_position(x, y)
    , m_size(size)
{}

template<typename T>
DRectT<T>::DRectT(const T x, const T y, const T width, const T height)
    : m_position(x, y)
    , m_size(width, height)
{}

template<typename T>
void DRectT<T>::set(const DPointT<T>& position, const DSizeT<T>& size)
{
    m_position = position;
    m_size = size;
}

template<typename T>
void DRectT<T>::set(const DPointT<T>& position, const T width, const T height)
{
    m_position = position;
    m_size.set(width, height);
}

template<typename T>
void DRectT<T>::set(const T x, const T y, const DSizeT<T>& size)
{
    m_position.set(x, y);
    m_size = size;
}

template<typename T>
void DRectT<T>::set(const T x, const T y, const T width, const T height)
{
    m_position.set(x, y);
    m_size.set(width, height);
}

template<typename T>
inline T DRectT<T>::x() const
{
    return m_position.x();
}

template<typename T>
void DRectT<T>::x(const T x)
{
    m_position.x(x);
}

template<typename T>
inline T DRectT<T>::y() const
{
    return m_position.y();
}

template<typename T>
void DRectT<T>::y(const T y)
{
    m_position.y(y);
}

template<typename T>
inline T DRectT<T>::width() const
{
    return m_size.width();
}

template<typename T>
void DRectT<T>::width(const T width)
{
    m_size.width(width);
}

template<typename T>
inline T DRectT<T>::height() const
{
    return m_size.height();
}

template<typename T>
void DRectT<T>::height(const T height)
{
    m_size.height(height);
}

template<typename T>
inline T DRectT<T>::left() const
{
    return m_position.x();
}

template<typename T>
void DRectT<T>::left(const T left)
{
    const T r = right();
    const T l = std::min<T>(r + 1, left);
    m_size.width(r - l + 1);
    m_position.x(l);
}

template<typename T>
inline T DRectT<T>::top() const
{
    return m_position.y();
}

template<typename T>
void DRectT<T>::top(const T top)
{
    const T b = bottom();
    const T t = std::min<T>(b + 1, top);
    m_size.height(b - t + 1);
    m_position.y(t);
}

template<typename T>
T DRectT<T>::right() const
{
    return m_position.x() + m_size.width() - 1;
}

template<typename T>
void DRectT<T>::right(const T right)
{
    const T l = left();
    const T r = std::max<T>(l - 1, right);
    m_size.width(r - l + 1);
}

template<typename T>
T DRectT<T>::bottom() const
{
    return m_position.y() + m_size.height() - 1;
}

template<typename T>
void DRectT<T>::bottom(const T bottom)
{
    const T t = top();
    const T b = std::max<T>(t - 1, bottom);
    m_size.height(b - t + 1);
}

template<typename T>
inline DPointT<T> DRectT<T>::leftTop() const
{
    return m_position;
}

template<typename T>
void DRectT<T>::leftTop(const DPointT<T>& point)
{
    left(point.x());
    top(point.y());
}

template<typename T>
void DRectT<T>::leftTop(const T l, const T t)
{
    left(l);
    top(t);
}

template<typename T>
DPointT<T> DRectT<T>::rightTop() const
{
    return DPointT<T>(right(), m_position.y());
}

template<typename T>
void DRectT<T>::rightTop(const DPointT<T>& point)
{
    right(point.x());
    top(point.y());
}

template<typename T>
void DRectT<T>::rightTop(const T r, const T t)
{
    right(r);
    top(t);
}

template<typename T>
DPointT<T> DRectT<T>::leftBottom() const
{
    return DPointT<T>(m_position.x(), bottom());
}

template<typename T>
void DRectT<T>::leftBottom(const DPointT<T>& point)
{
    left(point.x());
    bottom(point.y());
}

template<typename T>
void DRectT<T>::leftBottom(const T l, const T b)
{
    left(l);
    bottom(b);
}

template<typename T>
DPointT<T> DRectT<T>::rightBottom() const
{
    return DPointT<T>(right(), bottom());
}

template<typename T>
void DRectT<T>::rightBottom(const DPointT<T>& point)
{
    right(point.x());
    bottom(point.y());
}

template<typename T>
void DRectT<T>::rightBottom(const T r, const T b)
{
    right(r);
    bottom(b);
}

template<typename T>
DPointT<T> DRectT<T>::center() const
{
    return DPointT<T>(m_position.x() + m_size.width() / 2, m_position.y() + m_size.height() / 2);
}

template<typename T>
void DRectT<T>::center(const DPointT<T>& point)
{
    m_position += point - center();
}

template<typename T>
void DRectT<T>::center(const T x, const T y)
{
    center(DPointT<T>(x, y));
}

template<typename T>
inline const DPointT<T>& DRectT<T>::position() const
{
    return m_position;
}

template<typename T>
void DRectT<T>::position(const DPointT<T>& position)
{
    m_position = position;
}

template<typename T>
void DRectT<T>::position(const T x, const T y)
{
    m_position.set(x, y);
}

template<typename T>
inline const DSizeT<T>& DRectT<T>::size() const
{
    return m_size;
}

template<typename T>
void DRectT<T>::size(const DSizeT<T>& size)
{
    m_size = size;
}

template<typename T>
void DRectT<T>::size(const T width, const T height)
{
    m_size.set(width, height);
}

template<typename T>
inline T DRectT<T>::square() const
{
    return m_size.square();
}

template<typename T>
DPointT<T> DRectT<T>::localPoint(const DPointT<T>& absolutePoint) const
{
    return absolutePoint - m_position;
}

template<typename T>
DPointT<T> DRectT<T>::localPoint(const T x, const T y) const
{
    return DPointT<T>(x, y) - m_position;
}

template<typename T>
DPointT<T> DRectT<T>::absolutePoint(const DPointT<T>& localPoint) const
{
    return localPoint + m_position;
}

template<typename T>
DPointT<T> DRectT<T>::absolutePoint(const T x, const T y) const
{
    return DPointT<T>(x, y) + m_position;
}

template<typename T>
bool DRectT<T>::isIntersectedWith(const DRectT& rect) const
{
    return
        left()   <= rect.right()  &&
        top()    <= rect.bottom() &&
        right()  >= rect.left()   &&
        bottom() >= rect.top();
}

template<typename T>
bool DRectT<T>::contains(const DRectT& rect) const
{
    return rect.leftTop() >= leftTop() && rect.rightBottom() <= rightBottom();
}

template<typename T>
bool DRectT<T>::contains(const DPointT<T>& point) const
{
    return point >= leftTop() && point <= (rightBottom() - DPointT<T>(1, 1));
}

template<typename T>
bool DRectT<T>::isZero() const
{
    return m_size.isZero() && m_position.isZero();
}

template<typename T>
bool DRectT<T>::isEmpty() const
{
    return m_size.isEmpty();
}

template<typename T>
DRectT<T> DRectT<T>::operator*(const double value)
{
    return DRectT(m_size * value);
}

template<typename T>
DRectT<T>& DRectT<T>::operator*=(const double value)
{
    m_size *= value;
    return *this;
}

template<typename T>
DRectT<T> DRectT<T>::operator/(const double value)
{
    return DRectT(m_size / value);
}

template<typename T>
DRectT<T>& DRectT<T>::operator/=(const double value)
{
    m_size /= value;
    return *this;
}

template<typename T>
DRectT<T> DRectT<T>::operator|(const DRectT& rect) const
{
    return DRectT(*this) |= rect;
}

template<typename T>
DRectT<T> DRectT<T>::operator&(const DRectT& rect) const
{
    return DRectT(*this) &= rect;
}

template<typename T>
DRectT<T>& DRectT<T>::operator|=(const DRectT& rect)
{
    const auto l = std::min(left(),   rect.left());
    const auto t = std::min(top(),    rect.top());
    const auto r = std::max(right(),  rect.right());
    const auto b = std::max(bottom(), rect.bottom());

    left(l);
    top(t);
    right(r);
    bottom(b);

    return *this;
}

template<typename T>
DRectT<T>& DRectT<T>::operator&=(const DRectT& rect)
{
    const auto l = std::max(left(),   rect.left());
    const auto t = std::max(top(),    rect.top());
    const auto r = std::min(right(),  rect.right());
    const auto b = std::min(bottom(), rect.bottom());

    if(r < l || b < t)
    {
        m_position.set(0, 0);
        m_size.set(0, 0);
    }
    else
    {
        left(l);
        top(t);
        right(r);
        bottom(b);
    }

    return *this;
}

template<typename T>
bool DRectT<T>::operator==(const DRectT& rect) const
{
    return m_position == rect.m_position && m_size == rect.m_size;
}

template<typename T>
bool DRectT<T>::operator!=(const DRectT& rect) const
{
    return !operator==(rect);
}

template<typename T>
template<typename Func>
void DRectT<T>::forEach(Func func) const
{
    static_assert(is_callable_match<Func, void, T, T>, "Argument is not a function or functor.");

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
