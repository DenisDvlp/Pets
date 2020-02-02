//IDrawBufferNative.h
#pragma once
#include "IDrawBuffer.h"

template<typename T>
class IDrawBufferNative
    : public IDrawBuffer
{
public:
    virtual bool swap() = 0;
    virtual const T* buffer() = 0;
};