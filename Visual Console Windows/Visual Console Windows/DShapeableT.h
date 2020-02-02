//DShapeableT.h
#pragma once
#include "IDShapeable.h"

template<typename T>
class DShapeableT
    : public IDShapeable<T>
{
public:
    T          width() const                             override;
    T          height() const                            override;
    void       width(const T)                            override;
    void       height(const T)                           override;
    void       size(const T, const T)                    override;
    void       size(const DSizeT<T>&)                    override;
    DSizeT<T>  size() const                              override;
    T          x() const                                 override;
    T          y() const                                 override;
    void       x(const T)                                override;
    void       y(const T)                                override;
    void       position(const T, const T)                override;
    void       position(const DPointT<T>&)               override;
    DPointT<T> position() const                          override;
    T          left() const                              override;
    void       left(const T)                             override;
    T          top() const                               override;
    void       top(const T)                              override;
    T          right() const                             override;
    void       right(const T)                            override;
    T          bottom() const                            override;
    void       bottom(const T)                           override;
    DPointT<T> leftTop() const                           override;
    void       leftTop(const DPointT<T>&)                override;
    void       leftTop(const T, const T)                 override;
    DPointT<T> rightTop() const                          override;
    void       rightTop(const DPointT<T>&)               override;
    void       rightTop(const T, const T)                override;
    DPointT<T> leftBottom() const                        override;
    void       leftBottom(const DPointT<T>&)             override;
    void       leftBottom(const T, const T)              override;
    DPointT<T> rightBottom() const                       override;
    void       rightBottom(const DPointT<T>&)            override;
    void       rightBottom(const T, const T)             override;
    void       rect(const DPointT<T>&, const DSizeT<T>&) override;
    void       rect(const DPointT<T>&, const T, const T) override;
    void       rect(const T, const T, const DSizeT<T>&)  override;
    void       rect(const T, const T, const T, const T)  override;
    void       rect(const DRectT<T>&)                    override;
    DRectT<T>  rect() const                              override;
protected:
    virtual void reshape(DRectT<T>&);
private:
    DRectT<T> m_rect;
};

template<typename T>
inline T DShapeableT<T>::width() const
{
    return m_rect.width();
}

template<typename T>
inline T DShapeableT<T>::height() const
{
    return m_rect.height();
}

template<typename T>
void DShapeableT<T>::width(const T width)
{
    DRectT<T> rect(m_rect.x(), m_rect.y(), width, m_rect.height());
    reshape(rect);
    m_rect = rect;
}

template<typename T>
void DShapeableT<T>::height(const T height)
{
    DRectT<T> rect(m_rect.x(), m_rect.y(), m_rect.width(), height);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
void DShapeableT<T>::size(const T width, const T height)
{
    DRectT<T> rect(m_rect.x(), m_rect.y(), width, height);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
void DShapeableT<T>::size(const DSizeT<T>& size)
{
    DRectT<T> rect(m_rect.x(), m_rect.y(), size);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
inline DSizeT<T> DShapeableT<T>::size() const
{
    return m_rect.size();
}

template<typename T>
inline T DShapeableT<T>::x() const
{
    return m_rect.x();
}

template<typename T>
inline T DShapeableT<T>::y() const
{
    return m_rect.y();
}

template<typename T>
void DShapeableT<T>::x(const T x)
{
    DRectT<T> rect(x, m_rect.y(), m_rect.width(), m_rect.height());
    reshape(rect);
    m_rect = rect;
}

template<typename T>
void DShapeableT<T>::y(const T y)
{
    DRectT<T> rect(m_rect.x(), y, m_rect.width(), m_rect.height());
    reshape(rect);
    m_rect = rect;
}

template<typename T>
void DShapeableT<T>::position(const T x, const T y)
{
    DRectT<T> rect(x, y, m_rect.width(), m_rect.height());
    reshape(rect);
    m_rect = rect;
}

template<typename T>
void DShapeableT<T>::position(const DPointT<T>& position)
{
    DRectT<T> rect(position, m_rect.width(), m_rect.height());
    reshape(rect);
    m_rect = rect;
}

template<typename T>
inline DPointT<T> DShapeableT<T>::position() const
{
    return m_rect.position();
}

template<typename T>
inline T DShapeableT<T>::left() const
{
    return m_rect.left();
}

template<typename T>
void DShapeableT<T>::left(const T value)
{
    auto rect = m_rect;
    rect.left(value);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
inline T DShapeableT<T>::top() const
{
    return m_rect.top();
}

template<typename T>
void DShapeableT<T>::top(const T value)
{
    auto rect = m_rect;
    rect.top(value);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
inline T DShapeableT<T>::right() const
{
    return m_rect.right();
}

template<typename T>
void DShapeableT<T>::right(const T value)
{
    auto rect = m_rect;
    rect.right(value);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
inline T DShapeableT<T>::bottom() const
{
    return m_rect.bottom();
}

template<typename T>
void DShapeableT<T>::bottom(const T value)
{
    auto rect = m_rect;
    rect.bottom(value);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
inline DPointT<T> DShapeableT<T>::leftTop() const
{
    return m_rect.leftTop();
}

template<typename T>
void DShapeableT<T>::leftTop(const DPointT<T>& point)
{
    auto rect = m_rect;
    rect.leftTop(point);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
void DShapeableT<T>::leftTop(const T left, const T top)
{
    auto rect = m_rect;
    rect.leftTop(left, top);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
inline DPointT<T> DShapeableT<T>::rightTop() const
{
    return m_rect.rightTop();
}

template<typename T>
void DShapeableT<T>::rightTop(const DPointT<T>& point)
{
    auto rect = m_rect;
    rect.rightTop(point);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
void DShapeableT<T>::rightTop(const T right, const T top)
{
    auto rect = m_rect;
    rect.rightTop(right, top);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
inline DPointT<T> DShapeableT<T>::leftBottom() const
{
    return m_rect.leftBottom();
}

template<typename T>
void DShapeableT<T>::leftBottom(const DPointT<T>& point)
{
    auto rect = m_rect;
    rect.leftBottom(point);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
void DShapeableT<T>::leftBottom(const T left, const T bottom)
{
    auto rect = m_rect;
    rect.leftBottom(left, bottom);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
inline DPointT<T> DShapeableT<T>::rightBottom() const
{
    return m_rect.rightBottom();
}

template<typename T>
void DShapeableT<T>::rightBottom(const DPointT<T>& point)
{
    auto rect = m_rect;
    rect.rightBottom(point);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
void DShapeableT<T>::rightBottom(const T right, const T bottom)
{
    auto rect = m_rect;
    rect.rightBottom(right, bottom);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
void DShapeableT<T>::rect(const DPointT<T>& position, const DSizeT<T>& size)
{
    DRectT<T> rect(position, size);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
void DShapeableT<T>::rect(const DPointT<T>& position, const T width, const T height)
{
    DRectT<T> rect(position, width, height);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
void DShapeableT<T>::rect(const T x, const T y, const DSizeT<T>& size)
{
    DRectT<T> rect(x, y, size);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
void DShapeableT<T>::rect(const T x, const T y, const T width, const T height)
{
    DRectT<T> rect(x, y, width, height);
    reshape(rect);
    m_rect = rect;
}

template<typename T>
void DShapeableT<T>::rect(const DRectT<T>& rect)
{
    auto r = rect;
    reshape(r);
    m_rect = r;
}

template<typename T>
inline DRectT<T> DShapeableT<T>::rect() const
{
    return m_rect;
}

template<typename T>
inline void DShapeableT<T>::reshape(DRectT<T>&)
{}