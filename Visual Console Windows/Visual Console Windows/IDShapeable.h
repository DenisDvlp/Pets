//IDShapeable.h
#pragma once
#include "IDSizable.h"
#include "IDPositionable.h"
#include "DRect.h"

template<typename T>
class IDShapeable
    : public IDSizable<T>
    , public IDPositionable<T>
{
public:
    virtual            ~IDShapeable() = default;
    virtual T          left() const = 0;
    virtual void       left(const T) = 0;
    virtual T          top() const = 0;
    virtual void       top(const T) = 0;
    virtual T          right() const = 0;
    virtual void       right(const T) = 0;
    virtual T          bottom() const = 0;
    virtual void       bottom(const T) = 0;
    virtual DPointT<T> leftTop() const = 0;
    virtual void       leftTop(const DPointT<T>&) = 0;
    virtual void       leftTop(const T, const T) = 0;
    virtual DPointT<T> rightTop() const = 0;
    virtual void       rightTop(const DPointT<T>&) = 0;
    virtual void       rightTop(const T, const T) = 0;
    virtual DPointT<T> leftBottom() const = 0;
    virtual void       leftBottom(const DPointT<T>&) = 0;
    virtual void       leftBottom(const T, const T) = 0;
    virtual DPointT<T> rightBottom() const = 0;
    virtual void       rightBottom(const DPointT<T>&) = 0;
    virtual void       rightBottom(const T, const T) = 0;
    virtual void       rect(const DPointT<T>&, const DSizeT<T>&) = 0;
    virtual void       rect(const DPointT<T>&, const T, const T) = 0;
    virtual void       rect(const T, const T, const DSizeT<T>&) = 0;
    virtual void       rect(const T, const T, const T, const T) = 0;
    virtual void       rect(const DRectT<T>&) = 0;
    virtual DRectT<T>  rect() const = 0;
};
