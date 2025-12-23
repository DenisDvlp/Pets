//IDSizable.h
#pragma once
#include "DSize.hpp"

template<typename T>
class IDSizable
{
public:
    virtual           ~IDSizable() = default;
    virtual T         width()  const = 0;
    virtual T         height() const = 0;
    virtual void      width(const T) = 0;
    virtual void      height(const T) = 0;
    virtual void      size(const T, const T) = 0;
    virtual void      size(const DSizeT<T>&) = 0;
    virtual const DSizeT<T>& size() const = 0;
};
