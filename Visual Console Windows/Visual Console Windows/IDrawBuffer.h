//IDrawBuffer.h
#pragma once

class IDraw;

class IDrawBuffer
{
public:
    virtual ~IDrawBuffer() = default;
    virtual IDraw* beginDraw() = 0;
    virtual void endDraw() = 0;
};