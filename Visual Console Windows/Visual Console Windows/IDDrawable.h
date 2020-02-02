//IDDrawable.h
#pragma once

class IDDrawable
{
public:
    virtual ~IDDrawable() = default;
    virtual void draw() const = 0;
};