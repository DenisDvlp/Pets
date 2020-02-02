//ISizable.h
#pragma once

template<typename T>
class SizeT;

template<typename T>
class ISizable
{
public:
    virtual ~ISizable()     = default;
    virtual T width() const       = 0;
    virtual T height() const      = 0;
    virtual void width(T)         = 0;
    virtual void height(T)        = 0;
    virtual void size(T, T)       = 0;
    virtual void size(SizeT<T>)   = 0;
    virtual SizeT<T> size() const = 0;
};