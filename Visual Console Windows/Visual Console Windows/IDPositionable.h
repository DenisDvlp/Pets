//IDPositionable.h
#pragma once
#include "DPoint.h"

template<typename T>
class IDPositionable
{
public:
    virtual            ~IDPositionable() = default;
    virtual T          x() const = 0;
    virtual T          y() const = 0;
    virtual void       x(const T) = 0;
    virtual void       y(const T) = 0;
    virtual void       position(const T, const T) = 0;
    virtual void       position(const DPointT<T>&) = 0;
    virtual DPointT<T> position() const = 0;
};